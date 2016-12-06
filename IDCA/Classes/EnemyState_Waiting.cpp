#include "pch.h"
#include "Enemy.h"
#include "EnemyState_Waiting.h"
#include "EnemyState_Attack.h"
#include "EnemyState_Approach.h"

/*

Waiting

     Player의 공격을 기다리는 상태.

	1.     IsAttackedOnce가 True인 경우 Attacking상태로 돌입.
	2.     플래이어와의 거리가 Attack Range 이상인 경우, Approaching 상태로 돌입.

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
