#include "pch.h"
#include "Enemy.h"
#include "EnemyState_Waiting.h"
#include "EnemyState_Attack.h"
#include "EnemyState_Approach.h"

/*

Waiting

     Player�� ������ ��ٸ��� ����.

	1.     IsAttackedOnce�� True�� ��� Attacking���·� ����.
	2.     �÷��̾���� �Ÿ��� Attack Range �̻��� ���, Approaching ���·� ����.

*/


void EnemyState_Waiting::startState(Enemy* enemy)
{
}

void EnemyState_Waiting::runState(Enemy* enemy, float dt)
{
	float attackRange = enemy->getAttackRange();
	float distanceFromPlayer = enemy->getDistanceFromPlayer();

	if (!isPlayerInAttackRange(attackRange + WAITING_SCENE_CORRECTION_VALUE, distanceFromPlayer))
	{
		enemy->changeState<EnemyState_Approach>();
	}
	else if (enemy->getIsAttackedOnce())
	{
		enemy->changeState<EnemyState_Attack>();
	}
	else
	{
		enemy->Stop();
	}

	return;
}

void EnemyState_Waiting::endState(Enemy* enemy)
{
}

const int EnemyState_Waiting::returnStateNumber()
{
	return ENEMY_STATE_TYPE::WAITING;
}