#pragma once

#include "Core.h"
#include <vector>

class Actor;

class Engine_API Level
{
public:
	Level();
	virtual ~Level();

	// ������ ���͸� �߰��� �� ���
	void AddActor(Actor* _newActor);

	// ���� �̺�Ʈ �Լ�
	virtual void BeginPlay();
	virtual void Tick(float _deltaTime);
	virtual void Render();

private:
	std::vector<Actor*> actors; //������ ��ġ�� ��� ���͸� �����ϴ� �迭

};

