#pragma once
#include "EnemyState.h"

/*
*/

class BossState_Summon : public EnemyState
{
public:
	CREATE_FUNC(BossState_Summon);
	bool		init() override
	{
		setName("BossState_Summon");
		return true;
	}

	void		startState(Enemy* enemy) override;
	void		runState(Enemy* enemy, float dt) override;
	void		endState(Enemy* enemy) override;

	const int	returnStateNumber() override;
};