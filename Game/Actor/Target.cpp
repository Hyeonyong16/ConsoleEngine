#include "Target.h"

Target::Target(const Vector2& _position)
	: Actor('T', Color::Blue, _position)
{
	// �׸� �� ����� ���� ���� ����
	SetSortingOrder(1);
}
