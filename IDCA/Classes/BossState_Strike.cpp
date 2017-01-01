#include "pch.h"
#include "Enemy.h"
#include "BossState_Strike.h"
#include "BossState_Attack.h"


void BossState_Strike::startState(Enemy* enemy)
{

}

void BossState_Strike::runState(Enemy* enemy, float dt)
{
	// TODO :: Strike ±¸Çö.
	enemy->changeState<BossState_Attack>();
}

void BossState_Strike::endState(Enemy* enemy)
{

}

const int BossState_Strike::returnStateNumber()
{
	return ENEMY_STATE_TYPE::BOSS_STRIKE;
}