#include "pch.h"
#include "Enemy.h"
#include "BossState_Summon.h"
#include "EnemyState_Search.h"


void BossState_Summon::startState(Enemy* enemy)
{
	return;
}

void BossState_Summon::runState(Enemy* enemy, float dt)
{
	// TODO :: Player위치를 받고 그에 가장 가까운 Data Set 위치에 Enemy 생성.
	enemy->changeState<EnemyState_Search>();
	return;
}

void BossState_Summon::endState(Enemy* enemy)
{
	return;
}

const int BossState_Summon::returnStateNumber()
{
	return ENEMY_STATE_TYPE::BOSS_SUMMON;
}