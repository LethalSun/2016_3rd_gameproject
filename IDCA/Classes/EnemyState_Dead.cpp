#include "pch.h"
#include "SimpleAudioEngine.h"
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

// TODO :: pushedDistance를 enemy안의 멤버 변수로 등록하여 enemy마다 밀려나는 거 다르게 하기.
const int PushedActionTag = 1;
const float pushedDistance = 75.f;

void EnemyState_Dead::startState(Enemy* enemy)
{
	m_AccumulateTime = 0.f;

	// 마지막에 죽을 때는 두 배로 밀려나도록.
	auto pushedAction = MoveBy::create(enemy->getStiffTime(), -(enemy->getUnitVecToPlayer()) * pushedDistance);
	auto m_pEasePushedAction = EaseElasticInOut::create(pushedAction, enemy->getStiffTime() - 0.3f);
	m_pEasePushedAction->setTag(PushedActionTag);
	enemy->runAction(m_pEasePushedAction);

	// Fade out Action
	auto action = FadeOut::create(FADEOUT_TIME);
	enemy->m_pAnimationMaker->GetSprite()->runAction(action);

	// Enemy 메모리 해제 작업.
	auto manager = EnemyManager::getInstance();
	const int vecIdx = manager->FindEnemyWithPointer(enemy);

	// EnemyManager의 Vector에서 삭제.
	auto enemyVector = &manager->getEnemyVector();
	enemyVector->erase(vecIdx);

	// Sound 처리
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
	// EnemyManager의 deleteVector에 삽입.
	auto manager = EnemyManager::getInstance();
	auto deleteVector = &manager->getDeleteEenemyVector();
	deleteVector->pushBack(enemy);

	return;
}

const int EnemyState_Dead::returnStateNumber()
{
	return ENEMY_STATE_TYPE::DEAD;
}