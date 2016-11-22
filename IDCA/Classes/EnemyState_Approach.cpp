#include "pch.h"
#include "Enemy.h"
#include "EnemyState_Approach.h"
#include "EnemyState_Attack.h"
#include "EnemyState_Return.h"

/*
	Approaching

	�÷��̾ ���� UnitVec�� �ް�, �� �������� move�ϴ� ����.

	1.     AttackRange�ȿ� ���� ���, Attacking���·� ����.
	2.     �÷��̾���� �Ÿ��� ChasingRange�̻����� ������ ���, Returning���·� ����.
*/


void EnemyState_Approach::startState(Enemy* enemy)
{
	CCLOG("start_Approaching!");
}

void EnemyState_Approach::runState(Enemy* enemy, const float deltaTime)
{
	auto distanceFromPlayer = enemy->getDistanceFromPlayer();
	auto attackRange = enemy->getAttackRange();
	auto chaseRange = enemy->getChasingRange();

	if (isPlayerInAttackRange(attackRange, distanceFromPlayer))
	{
		enemy->changeState<EnemyState_Attack>();
	}
	else if (!isPlayerInChasingRange(chaseRange, distanceFromPlayer))
	{
		enemy->changeState<EnemyState_Return>();
	}
	else
	{
		enemy->CalUnitVecToPlayer();
		enemy->move(deltaTime);
	}

	return;
}

void EnemyState_Approach::endState(Enemy* enemy)
{
	CCLOG("end_Approach!");
}
