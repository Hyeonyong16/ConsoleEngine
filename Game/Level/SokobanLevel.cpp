#include "SokobanLevel.h"

#include <iostream>
#include "Math/Vector2.h"
#include "Utils/Utils.h"

#include "Actor/Player.h"
#include "Actor/Wall.h"
#include "Actor/Ground.h"
#include "Actor/Box.h"
#include "Actor/Target.h"

#include <Windows.h>
#include "Engine.h"


SokobanLevel::SokobanLevel()
{
	//ReadMapFile("Map.txt");
	ReadMapFile("Stage1.txt");
}

void SokobanLevel::Render()
{
	super::Render();

	// 게임 클리어 시 클리어 처리
	if (isGameClear)
	{
		Utils::SetConsolePosition({ 30, 0 });
		Utils::SetConsoleTextColor(static_cast<WORD>(Color::White));

		std::cout << "Game Clear!";
	}
}

void SokobanLevel::ReadMapFile(const char* _fileName)
{
	// 최종 에셋 경로 완성
	char filePath[256] = { };
	sprintf_s(filePath, 256, "../Assets/%s", _fileName);

	FILE* file = nullptr;
	fopen_s(&file, filePath, "rt");

	// 예외처리
	if (nullptr == file)
	{
		std::cout << "맵 파일 읽기 실패." << _fileName << "\n";
		__debugbreak();
		return;
	}

	// 파싱(Parcing, 해석)
	fseek(file, 0, SEEK_END);
	size_t fileSize = ftell(file);
	rewind(file);

	// 확인할 파일 크기를 활용해 버퍼 할당
	char* buffer = new char[fileSize + 1];
	//buffer[fileSize] = '\0';
	memset(buffer, 0, fileSize + 1);
	size_t readSize = fread(buffer, sizeof(char), fileSize, file);

	//// 파일 크기와 읽어들인 크기가 다른 경우
	//if (fileSize != readSize)
	//{
	//	std::cout << "fileSize is not matched with readSize\n";
	//}

	// 배열 순회를 위한 인덱스 변수
	int index = 0;

	// 문자열 길이 값
	int size = (int)readSize;
	
	// x, y 좌표
	Vector2 position;

	//문자 배열 순회
	while (index < size)
	{
		// 맵 문자 확인
		char mapCharacter = buffer[index++];

		// 개행 문자 처리
		if (mapCharacter == '\n')
		{
			// 다음 줄로 넘기면서, x 좌표 초기화
			++position.y;
			position.x = 0;

			continue;
		}

		//각 문자 처리
		switch (mapCharacter)
		{
		case '#':	// 벽
		case '1':
			AddActor(new Wall(position));
			break;
		case '.':	// 바닥
			AddActor(new Ground(position));
			break;
		case 'p':	// 플레이어
			AddActor(new Ground(position));
			AddActor(new Player(position));
			break;
		case 'b':	// 박스
			AddActor(new Ground(position));
			AddActor(new Box(position));
			break;
		case 't':	// 타겟
			AddActor(new Target(position));
			// 목표 점수 증가 처리
			++targetScore;
			break;
		}

		// x 좌표 증가 처리
		++position.x;
	}

	// 버퍼 해제
	delete[] buffer;

	// 파일 닫기
	fclose(file);
}

bool SokobanLevel::CheckGameClear()
{
	// 박스가 타겟 위치에 모두 옮겨졌는지 확인
	int currentScore = 0;

	// 타겟 액터 벡터에 저장
	std::vector<Actor*> targetActors;
	std::vector<Actor*> boxActors;
	for (Actor* const actor : actors)
	{
		// 타겟 액터이지 확인
		if (actor->As<Target>())
		{
			targetActors.emplace_back(actor);
		}

		// 박스 액터인지 확인
		else if (actor->As<Box>())
		{
			boxActors.emplace_back(actor);
		}
	}

	// 박스와 타겟 액터 위치 비교
	for (Actor* const targetActor : targetActors)
	{
		for (Actor* const boxActor : boxActors)
		{
			// 두 액터의 위치가 같으면 점수 증가 처리
			if (targetActor->GetPosition() == boxActor->GetPosition())
			{
				// 점수 증가
				++currentScore;
			}
		}
	}

	return currentScore == targetScore;
}

bool SokobanLevel::CanPlayerMove(const Vector2& _playerPosition, const Vector2& _newPosition)
{
	// 게임 클리어 여부 확인 및 종료 처리
	if (isGameClear)
	{
		return false;
	}

	// Box 처리
	std::vector<Box*> boxActors;
	for (Actor* const actor : actors)
	{
		Box* box = actor->As<Box>();
		if (box)
		{
			boxActors.emplace_back(box);
		}
	}

	// 이동하려는 위치에 박스가 있는지 확인
	Box* searchedBox = nullptr;
	for (Box* const boxActor : boxActors)
	{
		// 플레이어가 이동하려는 위치와 박스의 위치가 같은지 비교
		if (boxActor->GetPosition() == _newPosition)
		{
			// 같은 위치에 있는 박스 저장 후 루프 종료
			searchedBox = boxActor;
			break;
		}
	}

	// 이동하려는 위치에 박스가 있는 경우 처리
	if (nullptr != searchedBox)
	{
		// #1 : 박스를 이동시키려는 위치에 다른 박스가 또 있는지 확인
		Vector2 direction = _newPosition - _playerPosition;
		Vector2 nextPosition = searchedBox->GetPosition() + direction;

		for (Box* const otherBox : boxActors)
		{
			// 같은 박스는 건너뛰기
			if (otherBox == searchedBox)
			{
				continue;
			}

			// 박스를 이동시키려는 위치에 다른 박스가 있는지 확인
			if (otherBox->GetPosition() == nextPosition)
			{
				// 플레이어 이동 못함
				return false;
			}
		}

		for (Actor* const actor : actors)
		{
			if (actor->GetPosition() == nextPosition)
			{ 
				// #2 : 박스는 없지만, 벽이 있지 않은지 확인
				if (actor->As<Wall>())
				{
					// 플레이어 이동 못함
					return false;
				}

				// #3 : 이동 가능한 경우(그라운드, 타겟)에는 박스 이동 처리
				if (actor->As<Ground>() || actor->As<Target>())
				{
					// 박스 이동 처리
					searchedBox->SetPosition(nextPosition);

					// 게임 클리어 여부 확인
					isGameClear = CheckGameClear();

					// 플레이어 이동 가능
					return true;
				}
			}
		}
	}

	// 플레이어가 이동하려는 위치에 박스가 없는 경우
	for (Actor* const actor : actors)
	{
		if (actor->GetPosition() == _newPosition)
		{
			// 벽이면 이동 불가
			if (actor->As<Wall>())
			{
				return false;
			}

			// 그라운드 or 타겟
			return true;
		}
	}

	return false;
}
