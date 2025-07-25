#pragma once

#include "Core.h"
#include <Windows.h>


/*
*	Todo: 2025�� 7�� 25�� �۾��� ��
	- ������ �̱���(singleton) ���� �����
* 
*/
class Level;
class Engine_API Engine
{
	// Ű�Է� Ȯ���� ���� ����ü
	struct KeyState
	{
		bool isKeyDown = false;			// ���� �����ӿ� Ű�� ���ȴ��� ����
		bool previousKeyDown = false;	// ���� �����ӿ� Ű�� ���ȴ��� ����
	};

public:
	Engine();
	~Engine();

	// ���� ���� �Լ�
	void Run();

	// ���� �߰� �Լ�
	void AddLevel(Level* _newLevel);

	// Ű Ȯ�� �Լ�
	bool GetKey(int _keyCode);
	bool GetKeyDown(int _keyCode);
	bool GetKeyUp(int _keyCode);

	// ���� �Լ�
	void Quit();

	// �̱��� ���� �Լ�
	static Engine& Get();

private:
	// �ܺ� ���� ���� �Լ�
	void ProcessInput();
	
	void BeginPlay();
	void Tick(float _deltaTime = 0.f);
	void Render();

private:
	// ���� ���� �÷���
	bool isQuit = false;

	// Ű �Է� ���� ���� ����
	KeyState keyStates[255] = { };

	// ���� ����
	Level* mainLevel = nullptr;

	// �̱��� ����
	static Engine* instance;
};