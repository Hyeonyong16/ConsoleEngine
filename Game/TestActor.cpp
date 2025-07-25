#include "TestActor.h"
#include <iostream>
#include <Windows.h>

#include "Engine.h"

TestActor::TestActor()
	: Actor('P', Color::Red)
{ }

void TestActor::Tick(float _deltaTime)
{
	Actor::Tick(_deltaTime);
	super::Tick(_deltaTime);

	/*std::cout << "TestActor::Tick, FPS: "
		<< (1.0f / _deltaTime)
		<< "\n";*/

	if (Engine::Get().GetKey(VK_RIGHT) && GetPosition().x < 30)
	{
		Vector2 position = GetPosition();
		position.x += 1;
		SetPosition(position);
	}

	if (Engine::Get().GetKey(VK_LEFT) && GetPosition().x > 0)
	{
		Vector2 position = GetPosition();
		position.x -= 1;
		SetPosition(position);
	}

	if (Engine::Get().GetKey(VK_UP) && GetPosition().y > 0)
	{
		Vector2 position = GetPosition();
		position.y -= 1;
		SetPosition(position);
	}

	if (Engine::Get().GetKey(VK_DOWN) && GetPosition().y < 10)
	{
		Vector2 position = GetPosition();
		position.y += 1;
		SetPosition(position);
	}

	if (Engine::Get().GetKeyDown(VK_ESCAPE))
	{
		Engine::Get().Quit();
	}
}
