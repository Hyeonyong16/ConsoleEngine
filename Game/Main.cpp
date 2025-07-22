#include <iostream>
#include "Engine.h"
#include "Math/Vector2.h"

#ifdef _DEBUG
#define new new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
// allocations to be of _CLIENT_BLOCK type
#else
#define new new
#endif

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(18);

	Vector2 a(10, 20);
	Vector2 b(20, 30);
	std::cout << (a + b).ToString() << "\n";

	Engine engine;
	engine.Run();

	std::cin.get();
}