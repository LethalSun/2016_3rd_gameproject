#include "pch.h"
#include "Enemy.h"
#include "BossState_Summon.h"
#include "EnemyState_Search.h"
#include "EnemyManager.h"


void BossState_Summon::startState(Enemy* enemy)
{
	auto vector = enemy->m_pEnemyManager->getEnemyVector();
	auto size = vector.size();

	// ���� Enemy�� ���� �ۿ� �ȳ����� ���, ��ȯ ����.
	if (size == 1)
	{
		// ���ڷ� ��ȯ �ݰ��� �Ѱ���.
		enemy->m_pEnemyManager->AncientTreeSkillSummon(ANCIENT_TREE_SUMMON_RANGE);
	}

	return;
}

void BossState_Summon::runState(Enemy* enemy, float dt)
{
	// ��ȯ�� ������ Search���·� ����.
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