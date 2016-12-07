#include "pch.h"
#include "Enemy.h"
#include "EnemyState_Return.h"
#include "EnemyState_Approach.h"
#include "EnemyState_Search.h"

/*
Returning

현재 상태에서 Origin을 향한 UnitVec를 받고, 그 방향으로 move하는 상태.

1.       플레이어와의 거리가 ChasingRange - 300이하인 경우, Approaching 상태로 돌입.
2.       Origin과의 거리가 50인경우, Searching 상태로 돌입.

*/

const float returnEndRange = 50.f;

void EnemyState_Return::startState(Enemy* enemy)
{
	CCLOG("Start Return!");
}


void EnemyState_Return::runState(Enemy* enemy, float dt)
{
	float distanceFromPlayer = enemy->getDistanceFromPlayer();
	float distanceFromOrigin = enemy->getDistanceFromOrigin();
	float chaseRange = enemy->getChasingRange();

	if (isPlayerInChasingRange(chaseRange, distanceFromPlayer))
	{
		enemy->changeState<EnemyState_Approach>();
	}
	// TODO :: json 파일로 상수값 변환시키기.
	else if (distanceFromOrigin < returnEndRange)
	{
		enemy->changeState<EnemyState_Search>();
	}
	else
	{
		enemy->CalUnitVecToOrigin();
		enemy->MoveEnemy(dt);
	}

	return;
}


void EnemyState_Return::endState(Enemy* enemy)
{
	CCLOG("End Return");
}

const int EnemyState_Return::returnStateNumber()
{
	return ENEMY_STATE_TYPE::RETURN;
}