#include "pch.h"
#include "Enemy.h"
#include "BossState_Rush.h"
#include "BossState_Attack.h"
#include "EnemyState_Search.h"


void BossState_Rush::startState(Enemy* enemy)
{
	enemy->setcapturedUnitVecToPlayer(enemy->getUnitVecToPlayer());
	return;
}

void BossState_Rush::runState(Enemy* enemy, float dt)
{
	// TODO :: 일정 거리 or 시간 동안 capture된 unitVec으로 돌진.
	enemy->changeState<EnemyState_Search>();
	return;
}

void BossState_Rush::endState(Enemy* enemy)
{
	return;
}

const int BossState_Rush::returnStateNumber()
{
	return ENEMY_STATE_TYPE::BOSS_RUSH;
}