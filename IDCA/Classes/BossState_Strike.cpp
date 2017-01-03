#include "pch.h"
#include "Enemy.h"
#include "SimpleAudioEngine.h"
#include "BossState_Strike.h"
#include "BossState_Attack.h"
#include "AnimationMaker.h"
#include "Tentacle.h"

// Strike가 시작될 때, 점점 커지면서 붉게 변하여 플레이어에게 경고.
void BossState_Strike::startState(Enemy* enemy)
{
	// 커지고 붉어지는 액션 생성.
	auto biggerAction = ScaleTo::create(ANCIENT_TREE_STRIKE_RELEASE_TIME, ANCIENT_TREE_STRIKE_BIGGER_SCALE);
	auto redAction = TintBy::create(ANCIENT_TREE_STRIKE_RELEASE_TIME, 0, -255, -255);
	auto waitingAction = Spawn::create(biggerAction, redAction, nullptr);

	// 원상 복구하는 액션 생성.
	auto smallerAction = ScaleTo::create(ANCIENT_TREE_STRIKE_SHRINK_TIME, ANCIENT_TREE_STRIKE_NORMAL_SCALE);
	auto recoveryAction = TintBy::create(ANCIENT_TREE_STRIKE_SHRINK_TIME, 0, 255, 255);
	auto shrinkAction = Spawn::create(smallerAction, recoveryAction, nullptr);

	// 커졌다가 소리를 내면서 다시 작아지는 시퀀스 액션 생성.
	auto callFunc = CallFunc::create(CC_CALLBACK_0(BossState_Strike::MakeBossGrowl, this));
	auto seqAction = Sequence::create(waitingAction, callFunc, shrinkAction, nullptr);
	enemy->m_pAnimationMaker->GetSprite()->runAction(seqAction);
	
	m_AcculmulateTime = 0.f;
	return;
}

// 누적 시간이 일정 시간 이상이 되면 Strike를 실행하고 다시 Attack 상태로 복귀. 
void BossState_Strike::runState(Enemy* enemy, float dt)
{
	m_AcculmulateTime += dt;

	if (m_AcculmulateTime > ANCIENT_TREE_STRIKE_RELEASE_TIME + ANCIENT_TREE_STRIKE_RESTING_TIME)
	{
		enemy->Strike();
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

// 보스의 Strike 시행 소리를 내는 함수.
void BossState_Strike::MakeBossGrowl()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(ANCIENT_TREE_GROWL, false);
	return;
}

