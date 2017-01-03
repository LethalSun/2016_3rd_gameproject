#pragma once
#include "EnemyState.h"

/*
*/

class BossState_Rush : public EnemyState
{
public:
	CREATE_FUNC(BossState_Rush);
	bool		init() override
	{
		setName("BossState_Rush");
		return true;
	}

	void		startState(Enemy* enemy) override;
	void		runState(Enemy* enemy, float dt) override;
	void		endState(Enemy* enemy) override;

	const int	returnStateNumber() override;
	float		m_AcculmulateTime;
};