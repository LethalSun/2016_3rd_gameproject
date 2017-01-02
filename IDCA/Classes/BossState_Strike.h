#pragma once
#include "EnemyState.h"

/*
	BossState_Strike
	보스가 큰 공격을 하는 상태.
	큰 공격을 한 번 하고 나면 다시 Attack상태로 돌입.
*/

class BossState_Strike : public EnemyState
{
public:
	CREATE_FUNC(BossState_Strike);
	bool		init() override
	{
		setName("BossState_Strike");
		return true;
	}

	void		startState(Enemy* enemy) override;
	void		runState(Enemy* enemy, float dt) override;
	void		endState(Enemy* enemy) override;

	const int	returnStateNumber() override;
	float		m_AcculmulateTime;
	void		MakeBossGrowl();

};