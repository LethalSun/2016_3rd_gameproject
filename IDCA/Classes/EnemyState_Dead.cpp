#include "pch.h"
#include "SimpleAudioEngine.h"
#include "EnemyState_Dead.h"
#include "Enemy.h"
#include "EnemyManager.h"
#include "AnimationMaker.h"

/*
	Dead
	���ʹ��� Enemy�� 0���ϰ� �Ǹ� �����ϴ� ����.

	startState
		- ������� �׼� ����
		- EnemyManager�� EnemyVector���� �ٽ� Ȯ������ ���ϵ��� Vector���� erase.

	runState
		- �׼��� ��� ����� �� �ణ�� RESTING_TIME�� ��.
		- ���� endState ����.

	endState
		- MapPointer�� addChild �Ǿ� �־��� enemy�� removeChild�� ��.
*/

const float FADEOUT_TIME = 1.5f;
const float RESTING_TIME = 0.1f;

// TODO :: pushedDistance�� enemy���� ��� ������ ����Ͽ� enemy���� �з����� �� �ٸ��� �ϱ�.
const int PushedActionTag = 1;
const float pushedDistance = 75.f;

void EnemyState_Dead::startState(Enemy* enemy)
{
	m_AccumulateTime = 0.f;

	// �������� ���� ���� �� ��� �з�������.
	auto pushedAction = MoveBy::create(enemy->getStiffTime(), -(enemy->getUnitVecToPlayer()) * pushedDistance);
	auto m_pEasePushedAction = EaseElasticInOut::create(pushedAction, enemy->getStiffTime() - 0.3f);
	m_pEasePushedAction->setTag(PushedActionTag);
	enemy->runAction(m_pEasePushedAction);

	// Fade out Action
	auto action = FadeOut::create(FADEOUT_TIME);
	enemy->m_pAnimationMaker->GetSprite()->runAction(action);

	// Enemy �޸� ���� �۾�.
	auto manager = EnemyManager::getInstance();
	const int vecIdx = manager->FindEnemyWithPointer(enemy);

	// EnemyManager�� Vector���� ����.
	auto enemyVector = &manager->getEnemyVector();
	enemyVector->erase(vecIdx);

	// Sound ó��
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(enemy->getDyingSound(), false);

	return;
}

void EnemyState_Dead::runState(Enemy* enemy, const float deltaTime)
{
	m_AccumulateTime += deltaTime;

	if (m_AccumulateTime > FADEOUT_TIME + RESTING_TIME)
	{
		endState(enemy);
		return;
	}
}

void EnemyState_Dead::endState(Enemy* enemy)
{
	// EnemyManager�� deleteVector�� ����.
	auto manager = EnemyManager::getInstance();
	auto deleteVector = &manager->getDeleteEenemyVector();
	deleteVector->pushBack(enemy);

	return;
}

const int EnemyState_Dead::returnStateNumber()
{
	return ENEMY_STATE_TYPE::DEAD;
}