#pragma once

#include "Math/Vector2.h"

// �÷��̾ �̵��� �� �ִ��� Ȯ���� �� ����� �������̽�
class ICanPlayerMove
{
public:
	virtual bool CanPlayerMove(const Vector2& _playerPosition, const Vector2& _newPosition) = 0;

private:
};