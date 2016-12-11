#pragma once
#include "EnemyState.h"

class EnemyState_Search : public EnemyState
{
public:
	CREATE_FUNC(EnemyState_Search);
	bool		init() override
	{
		return true;
	}

	void		startState(Enemy* enemy) override;
	void		runState(Enemy* enemy, float dt) override;
	void		endState(Enemy* enemy) override;

	const int	returnStateNumber() override;
};