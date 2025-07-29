#pragma once

#include "Core.h"
#include "Input.h"
#include <Windows.h>


class Level;
class Engine_API Engine
{
public:
	Engine();

	virtual ~Engine();

	// 엔진 실행 함수
	void Run();

	// 레벨 추가 함수
	void AddLevel(Level* _newLevel);

	// 메모리 해제 함수
	virtual void CleanUp();

	// 종료 함수
	void Quit();

	// 싱글톤 접근 함수
	static Engine& Get();

private:	
	void BeginPlay();
	void Tick(float _deltaTime = 0.0f);
	void Render();

protected:
	// 엔진 종료 플래그
	bool isQuit = false;

	// 메인 레벨
	Level* mainLevel = nullptr;

	// 입력 관리자
	Input input;

	// 싱글톤 변수
	static Engine* instance;
};