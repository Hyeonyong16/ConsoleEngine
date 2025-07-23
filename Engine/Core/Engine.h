#pragma once

#include "Core.h"
#include <Windows.h>


/*
*	Todo: 2025년 7월 23일 작업할 것
	- 키 입력 관리 (KeyState 배열)								- 완료
	- 입력 확인 함수 (GetKey, GetKeyDown, GetKeyUp)			- 완료
	- Entity 추가 (Actor)									
	- 이벤트 함수 추가 (BeginPlay, Tick, Render)
	- Level 추가 (가상 공간에 배치된 물체(Actor) 관리 객체)
* 
*/
class Level;
class Engine_API Engine
{
	// 키입력 확인을 위한 구조체
	struct KeyState
	{
		bool isKeyDown = false;			// 현재 프레임에 키가 눌렸는지 여부
		bool previousKeyDown = false;	// 이전 프레임에 키가 눌렸는지 여부
	};

public:
	Engine();
	~Engine();

	// 엔진 실행 함수
	void Run();

	// 레벨 추가 함수
	void AddLevel(Level* _newLevel);

	// 키 확인 함수
	bool GetKey(int _keyCode);
	bool GetKeyDown(int _keyCode);
	bool GetKeyUp(int _keyCode);

	// 종료 함수
	void Quit();

private:
	// 외부 공개 안할 함수
	void ProcessInput();
	
	void BeginPlay();
	void Tick(float _deltaTime = 0.f);
	void Render();

private:
	// 엔진 종료 플래그
	bool isQuit = false;

	// 키 입력 정보 관리 변수
	KeyState keyStates[255] = { };

	// 메인 레벨
	Level* mainLevel = nullptr;
};