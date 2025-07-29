#pragma once
#include "Actor/Actor.h"

class Player : public Actor
{
	RTTI_DECLARATIONS(Player, Actor)

public:
	Player(const Vector2& _position);
	
	virtual void BeginPlay() override;
	virtual void Tick(float _deltaTime) override;

private:
	// 인터페이스 참조 변수
	class ICanPlayerMove* canPlayerMoveInterface = nullptr;
};

