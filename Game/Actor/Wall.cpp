#include "Wall.h"

Wall::Wall(const Vector2& _position)
	: Actor('#', Color::White, _position)
{
	// �׸� �� ����� ���� ���� ����
	SetSortingOrder(0);
}
