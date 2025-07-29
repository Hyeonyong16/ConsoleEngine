#include <iostream>
#include "Engine.h"
#include "Game/Game.h"

//#include "Demo/DemoLevel.h"
#include "Level/SokobanLevel.h"
#include "Level/MenuLevel.h"


int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(18);

	Game sokobanGame;
	//engine.AddLevel(new DemoLevel());
	//sokobanGame.AddLevel(new SokobanLevel());
	//sokobanGame.AddLevel(new MenuLevel());
	sokobanGame.Run();
}