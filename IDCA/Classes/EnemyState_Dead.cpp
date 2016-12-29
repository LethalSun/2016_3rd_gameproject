#include "pch.h"
#include "EnemyState_Dead.h"
#include "Enemy.h"
#include "EnemyManager.h"
#include "AnimationMaker.h"

/*
	Dead
	에너미의 Enemy가 0이하가 되면 진입하는 상태.

	startState
		- 사라지는 액션 실행
		- EnemyManager의 EnemyVector에서 다시 확인하지 못하도록 Vector에서 erase.

	runState
		- 액션이 모두 실행된 뒤 약간의 RESTING_TIME을 줌.
		- 이후 endState 실행.

	endState
		- MapPointer에 addChild 되어 있었던 enemy를 removeChild해 줌.
*/

const float FADEOUT_TIME = 1.5f;
const float RESTING_TIME = 0.1f;

void EnemyState_Dead::startState(Enemy* enemy)
{
	CCLOG("start_Dead!");
	m_AccumulateTime = 0.f;

	auto action = FadeOut::create(FADEOUT_TIME);
	enemy->m_pAnimationMaker->runAction(action);

	// Enemy 메모리 해제 작업.
	auto manager = EnemyManager::getInstance();
	const int vecIdx = manager->FindEnemyWithPointer(enemy);

	// EnemyManager의 Vector에서 삭제.
	auto enemyVector = &manager->getEnemyVector();
	enemyVector->erase(vecIdx);

	// EnemyManager의 deleteVector에 삽입.
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
	// TODO :: RemoveChild를 했는데 어째서 Update에 들어가서 죽는걸까?
	CCLOG("end_Dead!");

	return;
}

const int EnemyState_Dead::returnStateNumber()
{
	return ENEMY_STATE_TYPE::DEAD;
}