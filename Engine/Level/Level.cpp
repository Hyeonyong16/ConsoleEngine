#include "Level.h"
#include "Actor/Actor.h"

Level::Level()
{ }


Level::~Level()
{ 
	for (Actor* actor : actors)
	{
		SafeDelete(actor);
	}

	actors.clear();
}

// 레벨에 액터를 추가할 때 사용
void Level::AddActor(Actor* _newActor)
{
	// 예외처리(중복 여부 확인) 필요
	actors.emplace_back(_newActor);	// emplace_back 은 이동, push_back 은 참조 - 이동이 성능이 좋음

	// 오너십 설정
	_newActor->SetOwner(this);
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
	// 렌더링 전에 정렬 순서 기준으로 재배치
	SortActorsBySortingOrder();

	// Render Pass
	for (Actor* const actor : actors)
	{
		// 검사 ( 같은 위치에 정렬 순서가 높은 액터가 있는지 확인)
		Actor* searchedActor = nullptr;
		for (Actor* const otherActor : actors)
		{
			// 같은 액터면 무시
			if (actor == otherActor) continue;

			// 위치가 같은 액터 확인
			if (actor->GetPosition() == otherActor->GetPosition())
			{
				// 정렬 순서 비교 후 액터 저장
				if (actor->sortingOrder < otherActor->sortingOrder)
				{
					// 저장 및 루프 종료
					searchedActor = otherActor;
					break;
				}
			}
		}
		
		// 어떤 액터와 같은 위치에 정렬 순서가 더 높은 액터가 있으면 그리지 않고 건너뛰기
		if (nullptr != searchedActor)
		{
			continue;
		}

		// 드로우 콜
		actor->Render();
	}
}

// SortingOrder 에 따른 Actor 정렬
void Level::SortActorsBySortingOrder()
{
	// 버블 정렬
	for (int i = 0; i < (int)actors.size(); ++i)
	{
		for (int j = 0; j < (int)actors.size() - 1; ++j)
		{
			// sortingOrder 값이 클수록 뒤 쪽에 배치
			if (actors[j]->sortingOrder > actors[j + 1]->sortingOrder)
			{
				// 두 액터 위치 교환
				std::swap(actors[j], actors[j + 1]);
			}
		}
	}
	
}
