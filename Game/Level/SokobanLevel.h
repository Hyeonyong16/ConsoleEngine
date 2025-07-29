#pragma once

#include "Level/Level.h"
#include "Interface/ICanPlayerMove.h"

class SokobanLevel : public Level, public ICanPlayerMove
{
	RTTI_DECLARATIONS(SokobanLevel, Level)
public:
	SokobanLevel();

	virtual void Render() override;

	// ICanPlayerMove��(��) ���� ��ӵ�
	virtual bool CanPlayerMove(const Vector2& _playerPosition, const Vector2& _newPosition) override;

private:
	// �� ������ �о ���� ��ü �����ϴ� �Լ�
	void ReadMapFile(const char* _fileName);

	// ���� Ŭ���� Ȯ���ϴ� �Լ�
	bool CheckGameClear();

private:
	// ���� Ŭ��� ���� ����
	int targetScore = 0;

	// ���� Ŭ���� ���� Ȯ�� ����
	bool isGameClear = false;
};

