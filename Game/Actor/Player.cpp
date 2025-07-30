#include "Player.h"
#include "Engine.h"
#include "../Game/Game.h"
#include "Input.h"
#include "Level/Level.h"
#include "Interface/ICanplayerMove.h"

#include <iostream>

Player::Player(const Vector2& _position)
	: Actor('P', Color::Red, _position)
{
	// �׸� �� ����� ���� ���� ����
	SetSortingOrder(3);
}

void Player::BeginPlay()
{
	super::BeginPlay();

	// �������̽� ������
	if (nullptr != GetOwner())
	{
		canPlayerMoveInterface = dynamic_cast<ICanPlayerMove*>(GetOwner());

		if (nullptr == canPlayerMoveInterface)
		{
			std::cout << "Can not cast owner level to ICanPlayerMove.\n";
		}
	}
}

void Player::Tick(float _deltaTime)
{
	//Actor::Tick(_deltaTime);
	super::Tick(_deltaTime);

	// ESC �Է� �� ����
	if (Input::Get().GetKeyDown(VK_ESCAPE))
	{
		//QuitGame();
		Game::Get().ToggleMenu();
		return;
	}

	// �Է�ó��
	// �̵� ���� - �̵��ϱ� ���� �̵��� ��ġ�� �� �� �ִ��� �Ǵ� �� �̵�
	if (Input::Get().GetKeyDown(VK_RIGHT))
	{
		// �̵� ���� �̵� �������� Ȯ��
		if (canPlayerMoveInterface->CanPlayerMove(GetPosition(), Vector2(GetPosition().x + 1, GetPosition().y)))
		{
			Vector2 position = GetPosition();
			position.x += 1;
			SetPosition(position);
		}

	}
	if (Input::Get().GetKeyDown(VK_LEFT))
	{
		if(canPlayerMoveInterface->CanPlayerMove(
			GetPosition(),
			Vector2(GetPosition().x - 1, GetPosition().y)
		))
		{
			Vector2 position = GetPosition();
			position.x -= 1;
			SetPosition(position);
		}
	}
	if (Input::Get().GetKeyDown(VK_UP))
	{
		if (canPlayerMoveInterface->CanPlayerMove(
			GetPosition(),
			Vector2(GetPosition().x, GetPosition().y - 1)
		))
		{
			Vector2 position = GetPosition();
			position.y -= 1;
			SetPosition(position);
		}
		
	}
	if (Input::Get().GetKeyDown(VK_DOWN))
	{
		if (canPlayerMoveInterface->CanPlayerMove(
			GetPosition(),
			Vector2(GetPosition().x, GetPosition().y + 1)
		))
		{
			Vector2 position = GetPosition();
			position.y += 1;
			SetPosition(position);
		}
	}
}
