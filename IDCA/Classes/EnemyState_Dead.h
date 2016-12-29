#pragma once
#include "EnemyState.h"

class EnemyState_Dead : public EnemyState
{
public :
	CREATE_FUNC(EnemyState_Dead);
	bool init() override
	{
		setName("EnemyState_Dead");
		return true;
	}

	void		startState(Enemy* enemy) override;
	void		runState(Enemy* enemy, const float deltaTime) override;
	void		endState(Enemy* enemy) override;
	const int	returnStateNumber() override;

	float		m_AccumulateTime;
};