#include "pch.h"
#include "Enemy.h"
#include "EnemyState_Approach.h"
#include "EnemyState_Attack.h"
#include "EnemyState_Return.h"

/*
	Approaching

	플레이어를 향한 UnitVec를 받고, 그 방향으로 move하는 상태.

	1.     AttackRange안에 들어온 경우, Attacking상태로 돌입.
	2.     플레이어와의 거리가 ChasingRange이상으로 벌어진 경우, Returning상태로 돌입.
*/


void EnemyState_Approach::startState(Enemy* enemy)
{
}

void EnemyState_Approach::runState(Enemy* enemy, const float deltaTime)
{
	auto distanceFromPlayer = enemy->getDistanceFromPlayer();
	auto attackRange = enemy->getAttackRange();
	auto chaseRange = enemy->getChasingRange();

	// Settings for walk ( To Player )
	enemy->CalUnitVecToPlayer();
	enemy->TranslateUnitVec(enemy->getUnitVecToPlayer());
	enemy->CalDirection(enemy->getTranslatedUnitVec());

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
		enemy->MoveEnemy(deltaTime);
	}

	return;
}

void EnemyState_Approach::endState(Enemy* enemy)
{
}

const int EnemyState_Approach::returnStateNumber()
{
	return ENEMY_STATE_TYPE::APPROACHING;
}