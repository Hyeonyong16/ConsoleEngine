#include "Level.h"
#include "Actor/Actor.h"

Level::Level()
{ }


Level::~Level()
{ 
	for (int i = 0; i < actors.size(); ++i)
	{
		if (nullptr != actors[i])
		{
			delete actors[i];
		}
	}
	actors.clear();
}

// ������ ���͸� �߰��� �� ���
void Level::AddActor(Actor* _newActor)
{
	// ����ó��(�ߺ� ���� Ȯ��) �ʿ�
	actors.emplace_back(_newActor);	// emplace_back �� �̵�, push_back �� ���� - �̵��� ������ ����

}

// ���� �̺�Ʈ �Լ�
void Level::BeginPlay()
{
	for (Actor* const actor : actors)
	{
		if (actor->HasBeganPlay())
		{
			continue;
		}

		actor->BeginPlay();
	}
}

void Level::Tick(float _deltaTime)
{
	for (Actor* const actor : actors)
	{
		actor->Tick(_deltaTime);
	}
}


void Level::Render()
{ 
	for (Actor* const actor : actors)
	{
		actor->Render();
	}
}