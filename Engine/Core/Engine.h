#pragma once

#include "Core.h"
#include "Input.h"
#include <Windows.h>


class Level;
class Engine_API Engine
{
public:
	Engine();

	virtual ~Engine();

	// ���� ���� �Լ�
	void Run();

	// ���� �߰� �Լ�
	void AddLevel(Level* _newLevel);

	// �޸� ���� �Լ�
	virtual void CleanUp();

	// ���� �Լ�
	void Quit();

	// �̱��� ���� �Լ�
	static Engine& Get();

private:	
	void BeginPlay();
	void Tick(float _deltaTime = 0.0f);
	void Render();

protected:
	// ���� ���� �÷���
	bool isQuit = false;

	// ���� ����
	Level* mainLevel = nullptr;

	// �Է� ������
	Input input;

	// �̱��� ����
	static Engine* instance;
};