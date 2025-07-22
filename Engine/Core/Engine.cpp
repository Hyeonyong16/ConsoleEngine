#include "Engine.h"
#include <iostream>

// 단순 입력 처리(키보드)
// 타이머(시간 계산)

Engine::Engine()
{
}

Engine::~Engine()
{
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
			Update(deltaTime);
			Render();

			// 시간 업데이트
			previousTime = currentTime;
		}

	}
}

void Engine::Quit()
{
	// 종료 플래그 설정
	isQuit = true;
}

void Engine::ProcessInput()
{
	// ESC키 눌림 확인
	if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
	{
		// 종료
		Quit();
	}
}

void Engine::Update(float deltaTime)
{
	std::cout << "DeltaTime: " << deltaTime
		<< ", FPS: " << (1.f / deltaTime)
		<< "\n";
}

void Engine::Render()
{
}
