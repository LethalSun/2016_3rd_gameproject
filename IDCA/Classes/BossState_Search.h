#pragma once
#include "EnemyState.h"

class BossState_Search : public EnemyState
{
public :
	CREATE_FUNC(BossState_Search);
	bool init() override
	{
		setName("BossState_Search");
		return true;
	}

	void		startState(Enemy* enemy) override;
	void		runState(Enemy* enemy, float dt) override;
	void		endState(Enemy* enemy) override;

	const int	returnStateNumber() override;
};