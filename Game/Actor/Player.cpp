#include "Player.h"

#include <Windows.h>
#include "Engine.h"

Player::Player(const Vector2& _position)
	: Actor('P', Color::Red, _position)
{
	// 그릴 때 사용할 정렬 순서 설정
	SetSortingOrder(3);
}

void Player::Tick(float _deltaTime)
{
	//Actor::Tick(_deltaTime);
	super::Tick(_deltaTime);

	// ESC 입력 시 종료
	if (Engine::Get().GetKeyDown(VK_ESCAPE))
	{
		Engine::Get().Quit();
		return;
	}

	// @Todo: 입력처리 해야 함
	if (Engine::Get().GetKeyDown(VK_RIGHT))
	{
		Vector2 position = GetPosition();
		position.x += 1;
		SetPosition(position);
	}
	if (Engine::Get().GetKeyDown(VK_LEFT))
	{
		Vector2 position = GetPosition();
		position.x -= 1;
		SetPosition(position);
	}
	if (Engine::Get().GetKeyDown(VK_UP))
	{
		Vector2 position = GetPosition();
		position.y -= 1;
		SetPosition(position);
	}
	if (Engine::Get().GetKeyDown(VK_DOWN))
	{
		Vector2 position = GetPosition();
		position.y += 1;
		SetPosition(position);
	}
}
