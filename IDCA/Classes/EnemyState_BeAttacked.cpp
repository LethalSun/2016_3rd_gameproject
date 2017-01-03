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
	State���ۿ��� ó���ϴ� �͵�
		- Pushable �ʱ�ȭ.
		- PushAction ����.
		- RedAction ����.
		- �´� Sound ����. 
*/

void EnemyState_BeAttacked::startState(Enemy* enemy)
{
	m_Pushable = true;

	// Action ����.
	MakePushAction(enemy);
	MakeRedAction(enemy);
	
	// Sound ó��.
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

// Enemy�� �����͸� �޾� PushAction�� ���� �Ǻ��� ��, ����� ���� Action�� �ɾ��ش�.
void EnemyState_BeAttacked::MakePushAction(Enemy* enemy)
{
	// ������ ���, �з����� �ʴ´�.
	if (enemy->getEnemyType() == ENEMY_TYPE::ANCIENT_TREE)
	{
		return;
	}

	// ������ �ƴ� ���, Player���� UnitVec �ݴ�������� �з�����.
	auto pushedAction = MoveBy::create(enemy->getStiffTime(), -(enemy->getUnitVecToPlayer()) * ENEMY_PUSHED_DISTANCE);
	m_pEasePushedAction = EaseElasticInOut::create(pushedAction, enemy->getStiffTime() - ENEMY_PUSHED_CORRECTION_FLOAT);

	// ���� ��ֹ��� �ɸ� ��� Action�� ���߱� ���� Tag�� �ٿ� �����Ѵ�.
	m_pEasePushedAction->setTag(ENEMY_PUSHED_ACTION_TAG);
	enemy->runAction(m_pEasePushedAction);

	return;
}

// Enemy�� �����͸� �޾� RedAction�� ���� �Ǻ��� ��, ����� ���� Action�� �ɾ��ش�.
void EnemyState_BeAttacked::MakeRedAction(Enemy* enemy)
{
	// TintBy�� ����Ͽ� ������ �Ǵ� �׼ǰ� �ٽ� ���ƿ��� Action�� �����.
	enemy->m_pAnimationMaker->GetSprite()->stopActionByTag(TINT_ACTION_TAG);
	TintBy* redAction = TintBy::create(ENEMY_RED_ACTION_TIME, 0, -255, -255);
	TintBy* recoveryAction = TintBy::create(ENEMY_RED_ACTION_TIME, 0, 255, 255);

	auto seqAction = Sequence::create(redAction, recoveryAction, nullptr);
	seqAction->setTag(TINT_ACTION_TAG);
	enemy->m_pAnimationMaker->GetSprite()->runAction(seqAction);

	return;
}