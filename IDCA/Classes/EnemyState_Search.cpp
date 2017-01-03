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

// Searching ���� Player�� SearchingRange�ȿ� ������ Approach���·� ����.
void EnemyState_Search::runState(Enemy* enemy, float dt)
{
	// Enemy�� Sleeping������ ���, �ƹ� �͵� ���� �ʰ� State�� ��� �����.
	// Manager�� �����־�߸� Sleeping���¸� ��� �� �ִ�.
	if (enemy->getIsSleeping())
	{
		return;
	}
	// Searching Range�ȿ� Player�� �ִٸ� ���¸� �ٲ��ش�.
	else if (isPlayerInSearchRange(enemy->getSearchingRange(), enemy->getDistanceFromPlayer()))
	{
		// ���� Enemy�� Boss�� ���, �ٷ� ������ ���� State�� ��ȯ���ش�.
		if (enemy->getEnemyType() == ENEMY_TYPE::ANCIENT_TREE)
		{
			enemy->changeState<BossState_Attack>();
		}
		// �Ϲ� Enemy�� ���, Approach ���·� ��ȯ���ش�.
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
