#pragma once

#include "Core.h"
#include <Windows.h>

class Engine_API Engine
{
public:
	Engine();
	~Engine();

	// 엔진 실행 함수
	void Run();

	// 종료 함수
	void Quit();

private:
	// 외부 공개 안할 함수
	void ProcessInput();
	void Update(float deltaTime = 0.f);
	void Render();

private:
	// 엔진 종료 플래그
	bool isQuit = false;
};