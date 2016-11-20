#pragma once
#include "EnemyState.h"

class EnemyState_Approach: public EnemyState
{
public:
	CREATE_FUNC(EnemyState_Approach);
	bool		init() override
	{
		return true;
	}

	void		startState(Enemy* enemy) override;
	void		runState(Enemy* enemy, float dt) override;
	void		endState(Enemy* enemy) override;

};