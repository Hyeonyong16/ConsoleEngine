#include "Box.h"

Box::Box(const Vector2& _position)
	:Actor('B', Color::Green, _position)
{
	// �׸� �� ����� ���� ���� ����
	SetSortingOrder(2);
}
