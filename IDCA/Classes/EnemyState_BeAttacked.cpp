#include "pch.h"
#include "Enemy.h"
#include "EnemyState_BeAttacked.h"
#include "EnemyState_Search.h"
#include "AnimationMaker.h"

const float redTime = 0.1f;

void EnemyState_BeAttacked::startState(Enemy* enemy)
{
	auto redAction = TintTo::create(redTime, 121, 0, 0);
	auto recoveryAction = TintTo::create(redTime, 255, 255, 255);
	auto seqAction = Sequence::createWithTwoActions(redAction, recoveryAction);
	enemy->m_pAnimationMaker->GetSprite()->runAction(seqAction);
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
	enemy->setFlagBeAttacked(false);
	CCLOG("end_BeAttacked!");
}

const int EnemyState_BeAttacked::returnStateNumber()
{
	return ENEMY_STATE_TYPE::BE_ATTACKED;
}