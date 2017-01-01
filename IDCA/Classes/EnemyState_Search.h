#pragma once
#include "EnemyState.h"

/*
	EnemyState_Search
	작성자 : 이근원
	Enemy가 생긴 직후에 들어오는 상태.
	원점에서 Player가 자신의 SearchingRange안에 들어오는 것을 기다리고 있는 상태.
*/

class EnemyState_Search : public EnemyState
{
public:
	CREATE_FUNC(EnemyState_Search);
	bool		init() override
	{
		setName("EnemyState_Search");
		return true;
	}

	void		startState(Enemy* enemy) override;
	void		runState(Enemy* enemy, float dt) override;
	void		endState(Enemy* enemy) override;

	const int	returnStateNumber() override;
	float		m_AccumulateTime;
};