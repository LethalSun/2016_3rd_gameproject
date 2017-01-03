#include "pch.h"
#include "Enemy.h"
#include "EnemyState_Return.h"
#include "EnemyState_Approach.h"
#include "EnemyState_Search.h"

/*
	Returning
	현재 상태에서 Origin을 향한 UnitVec를 받고, 그 방향으로 move하는 상태.
*/


void EnemyState_Return::startState(Enemy* enemy)
{
}


void EnemyState_Return::runState(Enemy* enemy, float dt)
{
	float distanceFromPlayer = enemy->getDistanceFromPlayer();
	float distanceFromOrigin = enemy->getDistanceFromOrigin();
	float chaseRange = enemy->getChasingRange();
	Vec2 catchPosition = enemy->getPosition();

	// Settings for walk. ( To Origin )
	enemy->CalUnitVecToOrigin();
	enemy->TranslateUnitVec(enemy->getUnitVecToOrigin());
	enemy->CalDirection(enemy->getTranslatedUnitVec());

	if (isPlayerInChasingRange(chaseRange, distanceFromPlayer))
	{
		enemy->changeState<EnemyState_Approach>();
	}
	else if (distanceFromOrigin < STATE_RETURN_END_RANGE)
	{
		enemy->changeState<EnemyState_Search>();
	}
	else
	{
		enemy->MoveEnemy(dt);
		if (enemy->getPosition() == catchPosition)
		{
			enemy->setPosition(enemy->getOrigin());
		}
	}

	return;
}


void EnemyState_Return::endState(Enemy* enemy)
{
}

const int EnemyState_Return::returnStateNumber()
{
	return ENEMY_STATE_TYPE::RETURN;
}