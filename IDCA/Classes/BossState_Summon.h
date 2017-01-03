#pragma once
#include "EnemyState.h"

/*
	BossState_Summon
	작성자 : 이근원
	보스가 일정 수준 이하로 체력이 낮아질 때마다 들어와서 Enemy를 소환해주는 상태.
	미리 맵에 찍어놓은 적들의 좌표를 이용하여 플레이어 주변에 있는 적들을 소환해 준다.
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