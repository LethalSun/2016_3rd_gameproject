#include "pch.h"
#include "Enemy.h"
#include "EnemyState_BeAttacked.h"
#include "EnemyState_Search.h"
#include "AnimationMaker.h"
#include "ManageEnemyMove.h"
#include "ManageMap.h"
#include "EffectManager.h"

const float redTime = 0.3f;
const float pushedDistance = 75.f;
const int PushedActionTag = 1;

void EnemyState_BeAttacked::startState(Enemy* enemy)
{
	m_Pushable = true;
	auto redAction = TintTo::create(redTime, 121, 0, 0);
	auto recoveryAction = TintTo::create(redTime, 255, 255, 255);
	auto seqAction = Sequence::createWithTwoActions(redAction, recoveryAction);
	enemy->m_pAnimationMaker->GetSprite()->runAction(seqAction);

	enemy->m_pEffectManager->MakeEffect(3);
	
	

	// TODO :: 애니메이션을 넣으면 빨갛게 안변하는 것 고치기.
	auto pushedAction = MoveBy::create(enemy->getStiffTime(), -(enemy->getUnitVecToPlayer()) * pushedDistance);
	m_pEasePushedAction = EaseElasticInOut::create(pushedAction, enemy->getStiffTime() - 0.3f);
	m_pEasePushedAction->setTag(PushedActionTag);
	enemy->runAction(m_pEasePushedAction);

	CCLOG("start_BeAttacked!");
}

void EnemyState_BeAttacked::runState(Enemy* enemy, const float deltaTime)
{

	m_AccumulateTime += deltaTime;
	m_Pushable = enemy->getManageEnemyMove()->m_pManageMap->checkBlocked(enemy->getPosition(), - (enemy->getUnitVecToPlayer() *deltaTime), enemy->getMapPointer());

	if (!m_Pushable)
	{
		enemy->stopActionByTag(PushedActionTag);
	}

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