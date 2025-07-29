#include "Engine.h"
#include <iostream>
#include <Windows.h>

#include "Level/Level.h"
#include "Utils/Utils.h"

// ���� ���� �ʱ�ȭ
Engine* Engine::instance = nullptr;

BOOL WINAPI ConsoleMessageProcedure(DWORD _CtrlType)
{
	switch (_CtrlType)
	{
	case CTRL_CLOSE_EVENT:
		// Engine�� �޸� ����
		Engine::Get().CleanUp();
		return false;
	}

	return false;
}

Engine::Engine()
{
	// �̱����� ������ ��ü�� �ϳ��� �����ǰ� �ߺ� Ȯ���ؾ���
	// ���⼭�� ������ �ϳ��� ������ �� �˰� ������ �ϴ� ��ŵ
	instance = this;

	// �ܼ� Ŀ�� ����
	CONSOLE_CURSOR_INFO info;
	info.bVisible = false;
	info.dwSize = 1;

	SetConsoleCursorInfo(
		GetStdHandle(STD_OUTPUT_HANDLE),
		&info
	);

	// �ܼ� â �̺�Ʈ ���
	SetConsoleCtrlHandler(ConsoleMessageProcedure, TRUE);
}

Engine::~Engine()
{
	CleanUp();
}

void Engine::Run()
{
	// �и� ������ ������ ���� �ð��� �˷���
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
		input.ProcessInput();

		// ���� ������
		if(deltaTime >= oneFrameTime)
		{
			BeginPlay();
			Tick(deltaTime);
			Render();

			// �ð� ������Ʈ
			previousTime = currentTime;

			// ���� �������� �Է��� ���
			input.SavePreviousKeyStates();
		}

	}

	// ���� - �ؽ�Ʈ ���� ������� ��������
	Utils::SetConsoleTextColor(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
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

void Engine::CleanUp()
{
	// ���� ����
	SafeDelete(mainLevel);
}

void Engine::Quit()
{
	// ���� �÷��� ����
	isQuit = true;
}

Engine& Engine::Get()
{
	return *instance;
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
}

void Engine::Render()
{
	// ������ ���� �� �ؽ�Ʈ ������ �������
	Utils::SetConsoleTextColor(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);

	if (nullptr != mainLevel)
	{
		mainLevel->Render();
	}
}
