#pragma once
#include "EnemyState.h"

/*
	EnemyState_BeAttacked
	������ ����Ǵ� State.
	stiffTime �ð� ���� ������ ��, Search���·� �����Ѵ�.
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

};