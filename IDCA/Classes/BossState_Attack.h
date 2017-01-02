#pragma once
#include "EnemyState.h"
#include "Enemy_AncientTree.h"

/*
	BossState_Attack
	작성자 : 이근원
	Boss를 위해 새로 만들어 놓은 공격 상태.
	세 번 공격 후, Strike 공격 상태로 돌입.
	만약 Player가 range안에 없다면 마지막 유닛벡터를 저장해 놓은 후, rush상태로 돌입.
*/


class BossState_Attack : public EnemyState
{
public :
	CREATE_FUNC(BossState_Attack);
	bool init() override
	{
		setName("BossState_Attack");
		return true;
	}
	float		m_AccumulateTime = 0.f;

	void		startState(Enemy* enemy) override;
	void		runState(Enemy* enemy, float dt) override;
	void		endState(Enemy* enemy) override;

	const int	returnStateNumber() override;

	void		MakeTentacles(Enemy* enemy);
};