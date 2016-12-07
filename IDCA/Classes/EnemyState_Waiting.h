#pragma once
#include "EnemyState.h"

class EnemyState_Waiting : public EnemyState
{
public:
	CREATE_FUNC(EnemyState_Waiting);
	bool		init() override
	{
		return true;
	}

	void		startState(Enemy* enemy) override;
	void		runState(Enemy* enemy, float dt) override;
	void		endState(Enemy* enemy) override;

	const int	returnStateNumber() override;
};