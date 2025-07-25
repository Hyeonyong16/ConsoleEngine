#include "Engine.h"
#include <iostream>
#include <Windows.h>

#include "Level\Level.h"

// �ܼ� �Է� ó��(Ű����)
// Ÿ�̸�(�ð� ���)

// ���� ���� �ʱ�ȭ
Engine* Engine::instance = nullptr;

Engine::Engine()
{
	instance = this;

	// �ܼ� Ŀ�� ����
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
	// ���� ����
	if (nullptr != mainLevel)
	{
		delete mainLevel;
		mainLevel = nullptr;
	}
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
			BeginPlay();
			Tick(deltaTime);
			Render();

			// �ð� ������Ʈ
			previousTime = currentTime;

			// ���� �������� �Է��� ���
			for (int i = 0; i < 255; ++i)
			{
				keyStates[i].previousKeyDown = keyStates[i].isKeyDown;
			}
		}

	}

	// ����
	// �ؽ�Ʈ ���� ������� ��������
	SetConsoleTextAttribute(
		GetStdHandle(STD_OUTPUT_HANDLE),
		FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED
	);
}

void Engine::AddLevel(Level* _newLevel)
{
	// ������ �ִ� ������ ����
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
	// ���� �÷��� ����
	isQuit = true;
}

Engine& Engine::Get()
{
	// TODO: ���⿡ return ���� �����մϴ�.
	return *instance;
}

void Engine::ProcessInput()
{
	// Ű �Է� Ȯ��
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

	// ���� ������Ʈ
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
	// ������ ���� �� �ؽ�Ʈ ������ �������
	SetConsoleTextAttribute(
		GetStdHandle(STD_OUTPUT_HANDLE),
		FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED
	);

	if (nullptr != mainLevel)
	{
		mainLevel->Render();
	}
}
