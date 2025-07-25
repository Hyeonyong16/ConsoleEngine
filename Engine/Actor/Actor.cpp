#include "Actor.h"

#include <iostream>
#include <Windows.h>

Actor::Actor(const char _image, Color _color)
	: image(_image), color(_color)
{ }

Actor::~Actor()
{ }

// 이벤트 함수
// 객체 생애주기(Lifetime)에 1번만 호출(초기화 목적)
void Actor::BeginPlay()
{ 
	hasBeganPlay = true;
}

// 프레임마다 호출 (반복성 작업/지속성이 필요한 작업)
void Actor::Tick(float _deltaTime)
{ }

// 그리기 함수
void Actor::Render()
{
	// Win32 API
	// 커서 위치 이동

	// 콘솔 출력을 제어하는 핸들 얻어오기
	static HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	
	// 커서 위치 값 생성
	COORD coord = { (short)position.x, (short)position.y };
	
	// 커서 이동
	SetConsoleCursorPosition(handle, coord);
	
	// 색상 설정
	SetConsoleTextAttribute(handle, (WORD)color);

	// 그리기
	std::cout << image;
}

void Actor::SetPosition(const Vector2 & _newPosition)
{
	// 콘솔 출력을 제어하는 핸들 얻어오기
	static HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

	// 커서 위치 값 생성
	COORD coord = { (short)position.x, (short)position.y };

	// 커서 이동
	SetConsoleCursorPosition(handle, coord);

	// 색상 설정
	SetConsoleTextAttribute(handle, (WORD)color);

	// **임시** 기존 글씨를 지우고 이동
	std::cout << ' ';

	position = _newPosition;
}

Vector2 Actor::GetPosition() const
{
	return position;
}
