#include "SokobanLevel.h"

#include <iostream>
#include "Math/Vector2.h"

#include "Actor/Player.h"
#include "Actor/Wall.h"
#include "Actor/Ground.h"
#include "Actor/Box.h"
#include "Actor/Target.h"

#include <Windows.h>
#include "Engine.h"


SokobanLevel::SokobanLevel()
{
	ReadMapFile("Map.txt");
}

void SokobanLevel::ReadMapFile(const char* _fileName)
{
	// 최종 에셋 경로 완성
	char filePath[256] = { };
	sprintf_s(filePath, 256, "../Assets/%s", _fileName);

	FILE* file = nullptr;
	fopen_s(&file, filePath, "rb");

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

	// 파일 크기와 읽어들인 크기가 다른 경우
	if (fileSize != readSize)
	{
		std::cout << "fileSize is not matched with readSize\n";
	}

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

			// @Todo: 테스트용도. 나중에 삭제해야함.
			std::cout << "\n";
			continue;
		}

		//각 문자 처리
		switch (mapCharacter)
		{
		case '#':	// 벽
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
