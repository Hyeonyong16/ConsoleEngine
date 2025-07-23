#pragma once

#include "Core.h"
#include <Windows.h>


/*
*	Todo: 2025�� 7�� 23�� �۾��� ��
	- Ű �Է� ���� (KeyState �迭)								- �Ϸ�
	- �Է� Ȯ�� �Լ� (GetKey, GetKeyDown, GetKeyUp)			- �Ϸ�
	- Entity �߰� (Actor)									
	- �̺�Ʈ �Լ� �߰� (BeginPlay, Tick, Render)
	- Level �߰� (���� ������ ��ġ�� ��ü(Actor) ���� ��ü)
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
};