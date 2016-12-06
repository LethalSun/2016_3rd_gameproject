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
	CCLOG("Start Waiting");
}

void EnemyState_Waiting::runState(Enemy* enemy, float dt)
{
	float attackRange = enemy->getAttackRange();
	float distanceFromPlayer = enemy->getDistanceFromPlayer();

	char buf[255];
	sprintf(buf, "[Waiting] playerDistance : %f, AttackRange : %f, this X : %f, this Y : %f", enemy->getDistanceFromPlayer(), enemy->getAttackRange(), enemy->getPosition().x, enemy->getPosition().y);
	CCLOG(buf);

	if (!isPlayerInAttackRange(attackRange, distanceFromPlayer))
	{
		enemy->changeState<EnemyState_Approach>();
	}
	else if (enemy->getIsAttackedOnce())
	{
		enemy->changeState<EnemyState_Attack>();
	}

	return;
}

void EnemyState_Waiting::endState(Enemy* enemy)
{
	CCLOG("End Waiting");
}
