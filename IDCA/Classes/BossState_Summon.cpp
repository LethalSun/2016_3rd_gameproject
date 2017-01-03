#include "pch.h"
#include "Enemy.h"
#include "BossState_Summon.h"
#include "EnemyState_Search.h"
#include "EnemyManager.h"


void BossState_Summon::startState(Enemy* enemy)
{
	auto vector = enemy->m_pEnemyManager->getEnemyVector();
	auto size = vector.size();

	// 남은 Enemy가 보스 밖에 안남았을 경우, 소환 시작.
	if (size == 1)
	{
		// 인자로 소환 반경을 넘겨줌.
		enemy->m_pEnemyManager->AncientTreeSkillSummon(ANCIENT_TREE_SUMMON_RANGE);
	}

	return;
}

void BossState_Summon::runState(Enemy* enemy, float dt)
{
	// 소환이 끝나면 Search상태로 돌입.
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