#include "pch.h"
#include "Enemy.h"
#include "BossState_Summon.h"
#include "EnemyState_Search.h"
#include "EnemyManager.h"

const float summon_range = 200.f;

void BossState_Summon::startState(Enemy* enemy)
{
	// TODO :: 효과 넣기
	auto vector = enemy->m_pEnemyManager->getEnemyVector();
	auto size = vector.size();
	if (size == 1)
	{
		enemy->m_pEnemyManager->AncientTreeSkillSummon(summon_range);
	}

	return;
}

void BossState_Summon::runState(Enemy* enemy, float dt)
{
	// TODO :: Player위치를 받고 그에 가장 가까운 Data Set 위치에 Enemy 생성.
	enemy->changeState<EnemyState_Search>();
	return;
}

void BossState_Summon::endState(Enemy* enemy)
{
	return;
}

const int BossState_Summon::returnStateNumber()
{
	return ENEMY_STATE_TYPE::BOSS_SUMMON;
}