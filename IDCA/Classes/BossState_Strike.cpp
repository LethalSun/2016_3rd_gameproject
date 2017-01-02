#include "pch.h"
#include "Enemy.h"
#include "BossState_Strike.h"
#include "BossState_Attack.h"

const float releaseTime = 3.f;

void BossState_Strike::startState(Enemy* enemy)
{
	m_AcculmulateTime = 0.f;
}

void BossState_Strike::runState(Enemy* enemy, float dt)
{
	// TODO :: Strike ±¸Çö.
	m_AcculmulateTime += dt;

	if (m_AcculmulateTime > releaseTime)
	{
		enemy->changeState<BossState_Attack>();
	}

	return;
}

void BossState_Strike::endState(Enemy* enemy)
{
	return;
}

const int BossState_Strike::returnStateNumber()
{
	return ENEMY_STATE_TYPE::BOSS_STRIKE;
}