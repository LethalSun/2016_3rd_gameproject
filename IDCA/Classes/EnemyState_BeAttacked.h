#pragma once
#include "EnemyState.h"

/*
	EnemyState_BeAttacked
	작성자 : 이근원
	맞으면 실행되는 State.
	
	Enemy내부의 경직시간(StiffTime)동안 경직되었다가, Search 상태로 돌입한다.
	State내부에서 빨갛게 되는 Action과 밀리는 Action을 처리한다.
*/

class EnemyState_BeAttacked : public EnemyState
{
public:
	CREATE_FUNC(EnemyState_BeAttacked);
	bool		init() override
	{
		setName("EnemyState_BeAttacked");
		return true;
	}

	float		m_AccumulateTime = 0.f;

	void		startState(Enemy* enemy) override;
	void		runState(Enemy* enemy, const float deltaTime) override;
	void		endState(Enemy* enemy) override;
	const int   returnStateNumber() override;

	EaseElasticInOut* m_pEasePushedAction;
	bool        m_Pushable;
	void		MakePushAction(Enemy*);
	void		MakeRedAction(Enemy*);
};