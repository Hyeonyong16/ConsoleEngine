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

// 레벨에 액터를 추가할 때 사용
void Level::AddActor(Actor* _newActor)
{
	// 예외처리(중복 여부 확인) 필요
	actors.emplace_back(_newActor);	// emplace_back 은 이동, push_back 은 참조 - 이동이 성능이 좋음

}

// 엔진 이벤트 함수
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