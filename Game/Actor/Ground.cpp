#include "Ground.h"

Ground::Ground(const Vector2& _position)
	: Actor('.', Color::White, _position)
{
	// �׸� �� ����� ���� ���� ����
	SetSortingOrder(0);
}
