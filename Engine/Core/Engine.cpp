#include "Engine.h"
#include <iostream>
#include <Windows.h>

#include "Level\Level.h"

// 단순 입력 처리(키보드)
// 타이머(시간 계산)

// 정적 변수 초기화
Engine* Engine::instance = nullptr;

Engine::Engine()
{
	instance = this;

	// 콘솔 커서 끄기
	CONSOLE_CURSOR_INFO info;
	info.bVisible = false;
	info.dwSize = 1;

	SetConsoleCursorInfo(
		GetStdHandle(STD_OUTPUT_HANDLE),
		&info
	);
}

Engine::~Engine()
{
	// 레벨 삭제
	if (nullptr != mainLevel)
	{
		delete mainLevel;
		mainLevel = nullptr;
	}
}

void Engine::Run()
{
	// 밀리 세컨드 단위로 현재 시간을 알려줌
	//float currentTime = timeGetTime();
	LARGE_INTEGER currentTime;
	LARGE_INTEGER previousTime;
	QueryPerformanceCounter(&currentTime);
	previousTime = currentTime;

	// 하드웨어 시계의 정밀도(주파수) 가져오기
	// 나중에 초로 변환하기 위해
	LARGE_INTEGER frequency;
	QueryPerformanceFrequency(&frequency);

	// 타겟 프레임
	float targetFrameRate = 60.f;

	// 타겟 한 프레임 시간
	float oneFrameTime = 1.f / targetFrameRate;

	// GameLoop
	while (true)
	{
		// 엔진 종료 여부 확인
		if (isQuit)
		{ 
			// 루프 종료
			break; 
		}

		// 프레임 시간 계산
		// (현재 시간 - 이전 시간) / 주파수 = 초단위
		QueryPerformanceCounter(&currentTime);

		// 프레임 시간
		float deltaTime = (currentTime.QuadPart - previousTime.QuadPart) / (float)frequency.QuadPart;

		// 입력은 최대한 빠르게 처리
		ProcessInput();

		// 고정 프레임
		if(deltaTime >= oneFrameTime)
		{
			BeginPlay();
			Tick(deltaTime);
			Render();

			// 시간 업데이트
			previousTime = currentTime;

			// 현재 프레임의 입력을 기록
			for (int i = 0; i < 255; ++i)
			{
				keyStates[i].previousKeyDown = keyStates[i].isKeyDown;
			}
		}

	}

	// 정리
	// 텍스트 색상 원래대로 돌려놓기
	SetConsoleTextAttribute(
		GetStdHandle(STD_OUTPUT_HANDLE),
		FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED
	);
}

void Engine::AddLevel(Level* _newLevel)
{
	// 기존에 있던 레벨은 제거
	if (nullptr != mainLevel)
	{
		delete mainLevel;
	}

	mainLevel = _newLevel;
}

bool Engine::GetKey(int _keyCode)
{
	return keyStates[_keyCode].isKeyDown;
}

bool Engine::GetKeyDown(int _keyCode)
{
	return keyStates[_keyCode].isKeyDown && !keyStates[_keyCode].previousKeyDown;
}

bool Engine::GetKeyUp(int _keyCode)
{
	return !keyStates[_keyCode].isKeyDown && keyStates[_keyCode].previousKeyDown;
}

void Engine::Quit()
{
	// 종료 플래그 설정
	isQuit = true;
}

Engine& Engine::Get()
{
	// TODO: 여기에 return 문을 삽입합니다.
	return *instance;
}

void Engine::ProcessInput()
{
	// 키 입력 확인
	for (int i = 0; i < 255; ++i)
	{
		keyStates[i].isKeyDown = GetAsyncKeyState(i) & 0x8000;
	}
}

void Engine::BeginPlay()
{
	if (nullptr != mainLevel)
	{
		mainLevel->BeginPlay();
	}
}

void Engine::Tick(float _deltaTime)
{
	/*std::cout << "DeltaTime: " << _deltaTime
		<< ", FPS: " << (1.f / _deltaTime)
		<< "\n";*/

	// 레벨 업데이트
	if (nullptr != mainLevel)
	{
		mainLevel->Tick(_deltaTime);
	}

	/*if (GetKeyDown(VK_ESCAPE))
	{
		Quit();
	}*/
}

void Engine::Render()
{
	// 프레임 시작 시 텍스트 색상을 흰색으로
	SetConsoleTextAttribute(
		GetStdHandle(STD_OUTPUT_HANDLE),
		FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED
	);

	if (nullptr != mainLevel)
	{
		mainLevel->Render();
	}
}
