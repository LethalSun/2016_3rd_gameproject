#include "pch.h"
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

void EnemyState_Dead::startState(Enemy* enemy)
{
	CCLOG("start_Dead!");
	m_AccumulateTime = 0.f;

	auto action = FadeOut::create(FADEOUT_TIME);
	enemy->m_pAnimationMaker->runAction(action);

	// Enemy �޸� ���� �۾�.
	auto manager = EnemyManager::getInstance();
	const int vecIdx = manager->FindEnemyWithPointer(enemy);

	// EnemyManager�� Vector���� ����.
	auto enemyVector = &manager->getEnemyVector();
	enemyVector->erase(vecIdx);

	// EnemyManager�� deleteVector�� ����.
	auto deleteVector = &manager->getDeleteEenemyVector();
	deleteVector->pushBack(enemy);

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
	// TODO :: RemoveChild�� �ߴµ� ��°�� Update�� ���� �״°ɱ�?
	CCLOG("end_Dead!");

	return;
}

const int EnemyState_Dead::returnStateNumber()
{
	return ENEMY_STATE_TYPE::DEAD;
}