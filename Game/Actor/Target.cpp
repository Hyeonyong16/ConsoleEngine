#include "Target.h"

Target::Target(const Vector2& _position)
	: Actor('T', Color::Blue, _position)
{
	// 그릴 때 사용할 정렬 순서 설정
	SetSortingOrder(1);
}
