#include "pch.h"
#include "Enemy.h"
#include "SimpleAudioEngine.h"
#include "EnemyState_BeAttacked.h"
#include "EnemyState_Search.h"
#include "BossState_Rush.h"
#include "AnimationMaker.h"
#include "ManageEnemyMove.h"
#include "ManageMap.h"
#include "EffectManager.h"

/*
	State시작에서 처리하는 것들
		- Pushable 초기화.
		- PushAction 생성.
		- RedAction 생성.
		- 맞는 Sound 생성. 
*/

void EnemyState_BeAttacked::startState(Enemy* enemy)
{
	m_Pushable = true;

	// Action 생성.
	MakePushAction(enemy);
	MakeRedAction(enemy);
	
	// Sound 처리.
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(enemy->getHitedSound(), false);

}

void EnemyState_BeAttacked::runState(Enemy* enemy, const float deltaTime)
{

	m_AccumulateTime += deltaTime;
	m_Pushable = enemy->getManageEnemyMove()->m_pManageMap->checkBlocked(enemy->getPosition(), - (enemy->getUnitVecToPlayer() *deltaTime), enemy->getMapPointer());

	if (!m_Pushable)
	{
		enemy->stopActionByTag(ENEMY_PUSHED_ACTION_TAG);
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
}

const int EnemyState_BeAttacked::returnStateNumber()
{
	return ENEMY_STATE_TYPE::BE_ATTACKED;
}

// Enemy의 포인터를 받아 PushAction을 걸지 판별한 뒤, 결과에 따라 Action을 걸어준다.
void EnemyState_BeAttacked::MakePushAction(Enemy* enemy)
{
	// 보스일 경우, 밀려나지 않는다.
	if (enemy->getEnemyType() == ENEMY_TYPE::ANCIENT_TREE)
	{
		return;
	}

	// 보스가 아닌 경우, Player와의 UnitVec 반대방향으로 밀려난다.
	auto pushedAction = MoveBy::create(enemy->getStiffTime(), -(enemy->getUnitVecToPlayer()) * ENEMY_PUSHED_DISTANCE);
	m_pEasePushedAction = EaseElasticInOut::create(pushedAction, enemy->getStiffTime() - ENEMY_PUSHED_CORRECTION_FLOAT);

	// 만약 장애물에 걸릴 경우 Action을 멈추기 위해 Tag를 붙여 관리한다.
	m_pEasePushedAction->setTag(ENEMY_PUSHED_ACTION_TAG);
	enemy->runAction(m_pEasePushedAction);

	return;
}

// Enemy의 포인터를 받아 RedAction을 걸지 판별한 뒤, 결과에 따라 Action을 걸어준다.
void EnemyState_BeAttacked::MakeRedAction(Enemy* enemy)
{
	// TintBy를 사용하여 빨갛게 되는 액션과 다시 돌아오는 Action을 만든다.
	enemy->m_pAnimationMaker->GetSprite()->stopActionByTag(TINT_ACTION_TAG);
	TintBy* redAction = TintBy::create(ENEMY_RED_ACTION_TIME, 0, -255, -255);
	TintBy* recoveryAction = TintBy::create(ENEMY_RED_ACTION_TIME, 0, 255, 255);

	auto seqAction = Sequence::create(redAction, recoveryAction, nullptr);
	seqAction->setTag(TINT_ACTION_TAG);
	enemy->m_pAnimationMaker->GetSprite()->runAction(seqAction);

	return;
}