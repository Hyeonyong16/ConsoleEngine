#pragma once

#include "Level/Level.h"
#include "Actor/Actor.h"
#include <vector>

struct MenuItem
{
	// �Լ� ������ ����
	typedef void (*OnSelected)();

	MenuItem(const char* _text, OnSelected _onSelected)
		: onSelected(_onSelected)
	{
		// �޴� �ؽ�Ʈ ���ڿ� ����
		size_t length = strlen(_text) + 1;
		menuText = new char[length];
		strcpy_s(menuText, length, _text);
	}
	
	~MenuItem()
	{
		SafeDeleteArray(menuText);
	}

	// �޴� �ؽ�Ʈ
	char* menuText = nullptr;

	// �޴� ���� �� ������ ����
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
	// ���� ���õ� �������� �ε���
	int currentIndex = 0;

	// ������ ���� ����
	Color selectedColor = Color::Green;

	// ������ ���� �ȵ��� �� ����
	Color unselectedColor = Color::White;

	// ������ �迭
	std::vector<MenuItem*> items;

	// �޴� ������ ��
	int length = 0;

};