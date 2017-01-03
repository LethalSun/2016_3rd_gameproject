#pragma once
#include "EnemyState.h"

/*
	BossState_Rush
	작성자 : 이근원
	Player가 보스의 공격 범위 바깥으로 나갔을 경우, 플레이어로의 마지막 유닛벡터 방향으로 일정기간 달려가는 상태.
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