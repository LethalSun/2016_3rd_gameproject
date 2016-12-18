#include "pch.h"
#include "Enemy.h"
#include "EnemyState_BeAttacked.h"
#include "EnemyState_Search.h"


void EnemyState_BeAttacked::startState(Enemy* enemy)
{
	CCLOG("start_BeAttacked!");
}

void EnemyState_BeAttacked::runState(Enemy* enemy, const float deltaTime)
{
	m_AccumulateTime += deltaTime;

	if (m_AccumulateTime > enemy->getStiffTime())
	{
		m_AccumulateTime = 0.f;
		enemy->changeState<EnemyState_Search>();
	}

	return;
}

void EnemyState_BeAttacked::endState(Enemy* enemy)
{
	CCLOG("end_BeAttacked!");
}

const int EnemyState_BeAttacked::returnStateNumber()
{
	return ENEMY_STATE_TYPE::BE_ATTACKED;
}