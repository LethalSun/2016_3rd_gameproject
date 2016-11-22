#pragma once
#include "EnemyState.h"

class EnemyState_Attack : public EnemyState
{
public:
	CREATE_FUNC(EnemyState_Attack);
	bool		init() override
	{
		return true;
	}

	void		startState(Enemy* enemy) override;
	void		runState(Enemy* enemy, const float deltaTime) override;
	void		endState(Enemy* enemy) override;

};