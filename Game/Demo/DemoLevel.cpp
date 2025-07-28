#include "DemoLevel.h"
#include "TestActor.h"

#include <iostream>

DemoLevel::DemoLevel()
{
	AddActor(new TestActor());

	// 테스트로 맵 파일 읽기.
	FILE* file = nullptr;
	fopen_s(&file, "../Assets/Map.txt", "rb");

	if (nullptr == file)
	{
		std::cout << "Failed to open Map.txt file.\n";
		__debugbreak();
		return;
	}

	// 파일 크기 확인
	// 파일 위치(File Position) 커서를 제일 끝으로 이동
	fseek(file, 0, SEEK_END);

	// 이동한 지점의 위치 반환.
	size_t fileSize = ftell(file);

	// 파일 위치 커서 되돌리기.
	//fseek(file, 0, SEEK_SET);
	rewind(file);

	// 데이터 저장을 위한 버퍼 할당
	//char* buffer = new char[fileSize + 1];
	char buffer[256] = { };

	// 파일 종료시점까지 반복
	while (!feof(file))
	{
		// 한 줄씩 읽기
		fgets(buffer, 256, file);

		// 한 줄 문자열의 길이값 구하기
		int lineLength = (int)strlen(buffer);

		// 파싱 (Parcing, 해석)
		for (int i = 0; i < lineLength; ++i)
		{
			char mapCharacter = buffer[i];

			switch (mapCharacter)
			{
			case '#':
				std::cout << '#';
				break;
			case '.':
				std::cout << '.';
				break;
			case 'p':
				std::cout << 'p';
				break;
			case 'b':
				std::cout << 'b';
				break;
			case 't':
				std::cout << 't';
				break;

			default:
				break;
			}
		}

		// 개행 (엔터)
		std::cout << "\n";

	}

	// 파일 닫기
	fclose(file);

}
