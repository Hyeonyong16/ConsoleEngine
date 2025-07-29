#pragma once

#include "Level/Level.h"
#include "Actor/Actor.h"
#include <vector>

struct MenuItem
{
	// 함수 포인터 선언
	typedef void (*OnSelected)();

	MenuItem(const char* _text, OnSelected _onSelected)
		: onSelected(_onSelected)
	{
		// 메뉴 텍스트 문자열 복사
		size_t length = strlen(_text) + 1;
		menuText = new char[length];
		strcpy_s(menuText, length, _text);
	}
	
	~MenuItem()
	{
		SafeDeleteArray(menuText);
	}

	// 메뉴 텍스트
	char* menuText = nullptr;

	// 메뉴 선택 시 실행할 동작
	OnSelected onSelected = nullptr;
};

class MenuLevel : public Level
{
	RTTI_DECLARATIONS(MenuLevel, Level)

public:
	MenuLevel();
	~MenuLevel();

	virtual void Tick(float _deltaTime) override;
	virtual void Render() override;

private:
	// 현재 선택된 아이템의 인덱스
	int currentIndex = 0;

	// 아이템 선택 색상
	Color selectedColor = Color::Green;

	// 아이템 선택 안됐을 때 색상
	Color unselectedColor = Color::White;

	// 아이템 배열
	std::vector<MenuItem*> items;

	// 메뉴 아이템 수
	int length = 0;

};