#pragma once

#include "Core.h"
#include <Windows.h>

class Engine_API Engine
{
public:
	Engine();
	~Engine();

	// ���� ���� �Լ�
	void Run();

	// ���� �Լ�
	void Quit();

private:
	// �ܺ� ���� ���� �Լ�
	void ProcessInput();
	void Update(float deltaTime = 0.f);
	void Render();

private:
	// ���� ���� �÷���
	bool isQuit = false;
};