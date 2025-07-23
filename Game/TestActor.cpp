#include "TestActor.h"
#include <iostream>

void TestActor::Tick(float _deltaTime)
{
	Actor::Tick(_deltaTime);

	std::cout << "TestActor::Tick, FPS: "
		<< (1.0f / _deltaTime)
		<< "\n";
}
