#include "Actor.h"

#include <iostream>
#include <Windows.h>

Actor::Actor(const char _image, Color _color)
	: image(_image), color(_color)
{ }

Actor::~Actor()
{ }

// �̺�Ʈ �Լ�
// ��ü �����ֱ�(Lifetime)�� 1���� ȣ��(�ʱ�ȭ ����)
void Actor::BeginPlay()
{ 
	hasBeganPlay = true;
}

// �����Ӹ��� ȣ�� (�ݺ��� �۾�/���Ӽ��� �ʿ��� �۾�)
void Actor::Tick(float _deltaTime)
{ }

// �׸��� �Լ�
void Actor::Render()
{
	// Win32 API
	// Ŀ�� ��ġ �̵�

	// �ܼ� ����� �����ϴ� �ڵ� ������
	static HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	
	// Ŀ�� ��ġ �� ����
	COORD coord = { (short)position.x, (short)position.y };
	
	// Ŀ�� �̵�
	SetConsoleCursorPosition(handle, coord);
	
	// ���� ����
	SetConsoleTextAttribute(handle, (WORD)color);

	// �׸���
	std::cout << image;
}

void Actor::SetPosition(const Vector2 & _newPosition)
{
	// �ܼ� ����� �����ϴ� �ڵ� ������
	static HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

	// Ŀ�� ��ġ �� ����
	COORD coord = { (short)position.x, (short)position.y };

	// Ŀ�� �̵�
	SetConsoleCursorPosition(handle, coord);

	// ���� ����
	SetConsoleTextAttribute(handle, (WORD)color);

	// **�ӽ�** ���� �۾��� ����� �̵�
	std::cout << ' ';

	position = _newPosition;
}

Vector2 Actor::GetPosition() const
{
	return position;
}
