#include "Engine.h"
#include <iostream>

// �ܼ� �Է� ó��(Ű����)
// Ÿ�̸�(�ð� ���)

Engine::Engine()
{
}

Engine::~Engine()
{
}

void Engine::Run()
{
	// �и� ������ ������ ���� �ð��� �˷���
	//float currentTime = timeGetTime();
	LARGE_INTEGER currentTime;
	LARGE_INTEGER previousTime;
	QueryPerformanceCounter(&currentTime);
	previousTime = currentTime;

	// �ϵ���� �ð��� ���е�(���ļ�) ��������
	// ���߿� �ʷ� ��ȯ�ϱ� ����
	LARGE_INTEGER frequency;
	QueryPerformanceFrequency(&frequency);

	// Ÿ�� ������
	float targetFrameRate = 60.f;

	// Ÿ�� �� ������ �ð�
	float oneFrameTime = 1.f / targetFrameRate;

	// GameLoop
	while (true)
	{
		// ���� ���� ���� Ȯ��
		if (isQuit)
		{ 
			// ���� ����
			break; 
		}

		// ������ �ð� ���
		// (���� �ð� - ���� �ð�) / ���ļ� = �ʴ���
		QueryPerformanceCounter(&currentTime);

		// ������ �ð�
		float deltaTime = (currentTime.QuadPart - previousTime.QuadPart) / (float)frequency.QuadPart;

		// �Է��� �ִ��� ������ ó��
		ProcessInput();

		// ���� ������
		if(deltaTime >= oneFrameTime)
		{
			Update(deltaTime);
			Render();

			// �ð� ������Ʈ
			previousTime = currentTime;
		}

	}
}

void Engine::Quit()
{
	// ���� �÷��� ����
	isQuit = true;
}

void Engine::ProcessInput()
{
	// ESCŰ ���� Ȯ��
	if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
	{
		// ����
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
