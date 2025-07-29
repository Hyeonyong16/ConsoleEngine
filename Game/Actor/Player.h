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
	// �������̽� ���� ����
	class ICanPlayerMove* canPlayerMoveInterface = nullptr;
};

