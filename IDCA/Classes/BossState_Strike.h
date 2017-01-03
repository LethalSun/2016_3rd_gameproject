#pragma once
#include "EnemyState.h"

/*
	BossState_Strike
	������ ū ������ �ϴ� ����.
	ū ������ �� �� �ϰ� ���� �ٽ� Attack���·� ����.
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