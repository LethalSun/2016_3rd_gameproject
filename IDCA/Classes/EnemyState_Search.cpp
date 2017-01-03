#include "pch.h"
#include "Enemy.h"
#include "EnemyState_Search.h"
#include "BossState_Attack.h"
#include "EnemyState_Approach.h"
#include "BossState_Summon.h"




void EnemyState_Search::startState(Enemy* enemy)
{
	m_AccumulateTime = 0.f;
	return;
}

// Searching 도중 Player가 SearchingRange안에 들어오면 Approach상태로 돌입.
void EnemyState_Search::runState(Enemy* enemy, float dt)
{
	// Enemy가 Sleeping상태일 경우, 아무 것도 하지 않고 State는 계속 종료됨.
	// Manager가 깨워주어야만 Sleeping상태를 벗어날 수 있다.
	if (enemy->getIsSleeping())
	{
		return;
	}
	// Searching Range안에 Player가 있다면 상태를 바꿔준다.
	else if (isPlayerInSearchRange(enemy->getSearchingRange(), enemy->getDistanceFromPlayer()))
	{
		// 만약 Enemy가 Boss일 경우, 바로 보스의 공격 State로 전환해준다.
		if (enemy->getEnemyType() == ENEMY_TYPE::ANCIENT_TREE)
		{
			enemy->changeState<BossState_Attack>();
		}
		// 일반 Enemy일 경우, Approach 상태로 전환해준다.
		else
		{
			enemy->changeState<EnemyState_Approach>();
		}
	}

	return;
}

void EnemyState_Search::endState(Enemy* enemy)
{
	return;
}

const int EnemyState_Search::returnStateNumber()
{
	return ENEMY_STATE_TYPE::SEARCHING;
}
