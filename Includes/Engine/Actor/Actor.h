#pragma once

#include "Core.h"
#include "Math\Vector2.h"
#include "RTTI.h"

// Actor 정의
// 1. 위치 점령
// 2. 콘솔 창에 그리기(어떻게/무엇을)
// 3. 엔진의 이벤트 함수 호출(BeginPlay/Tick/Draw)
//

class Engine_API Actor : public RTTI		// 최근은 RTTI 가 아닌 Object 이름으로 자주 사용
{
	RTTI_DECLARATIONS(Actor, RTTI)			// 왼쪽은 자손, 오른쪽은 부모타입 지정

public:
	Actor();
	virtual ~Actor();

	// 이벤트 함수
	virtual void BeginPlay();				// 객체 생애주기(Lifetime)에 1번만 호출(초기화 목적)
	virtual void Tick(float _deltaTime);		// 프레임마다 호출 (반복성 작업/지속성이 필요한 작업)
	virtual void Render();					// 그리기 함수

	// BeginPlay 함수 호출 여부 
	inline bool HasBeganPlay() const { return hasBeganPlay; }

private:
	Vector2 position;	// 개체의 위치
	char image = ' ';	// 그릴 값
	bool hasBeganPlay = false; // BeginPlay 호출이 되었는지 확인
};

