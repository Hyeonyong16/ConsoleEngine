#pragma once

#include "Core.h"
#include "Math\Vector2.h"
#include "RTTI.h"

// Actor ����
// 1. ��ġ ����
// 2. �ܼ� â�� �׸���(���/������)
// 3. ������ �̺�Ʈ �Լ� ȣ��(BeginPlay/Tick/Draw)
//

class Engine_API Actor : public RTTI		// �ֱ��� RTTI �� �ƴ� Object �̸����� ���� ���
{
	RTTI_DECLARATIONS(Actor, RTTI)			// ������ �ڼ�, �������� �θ�Ÿ�� ����

public:
	Actor();
	virtual ~Actor();

	// �̺�Ʈ �Լ�
	virtual void BeginPlay();				// ��ü �����ֱ�(Lifetime)�� 1���� ȣ��(�ʱ�ȭ ����)
	virtual void Tick(float _deltaTime);		// �����Ӹ��� ȣ�� (�ݺ��� �۾�/���Ӽ��� �ʿ��� �۾�)
	virtual void Render();					// �׸��� �Լ�

	// BeginPlay �Լ� ȣ�� ���� 
	inline bool HasBeganPlay() const { return hasBeganPlay; }

private:
	Vector2 position;	// ��ü�� ��ġ
	char image = ' ';	// �׸� ��
	bool hasBeganPlay = false; // BeginPlay ȣ���� �Ǿ����� Ȯ��
};

