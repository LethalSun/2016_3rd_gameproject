#include "pch.h"
#include "Enemy.h"
#include "SimpleAudioEngine.h"
#include "BossState_Strike.h"
#include "BossState_Attack.h"
#include "AnimationMaker.h"
#include "Tentacle.h"

const float releaseTime = 3.f;
const float shrinkTime = 0.01f;
const float restingTime = 0.1f;

void BossState_Strike::startState(Enemy* enemy)
{
	auto biggerAction = ScaleTo::create(releaseTime, 1.6);
	auto redAction = TintBy::create(releaseTime, 0, -255, -255);
	auto waitingAction = Spawn::create(biggerAction, redAction, nullptr);

	auto smallerAction = ScaleTo::create(shrinkTime, 1.0);
	auto recoveryAction = TintBy::create(shrinkTime, 0, 255, 255);
	auto shrinkAction = Spawn::create(smallerAction, recoveryAction, nullptr);

	auto callFunc = CallFunc::create(CC_CALLBACK_0(BossState_Strike::MakeBossGrowl, this));
	auto seqAction = Sequence::create(waitingAction, callFunc, shrinkAction, nullptr);
	enemy->m_pAnimationMaker->GetSprite()->runAction(seqAction);
	
	m_AcculmulateTime = 0.f;
}

void BossState_Strike::runState(Enemy* enemy, float dt)
{
	// TODO :: Strike ±¸Çö.
	m_AcculmulateTime += dt;

	if (m_AcculmulateTime > releaseTime + restingTime)
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

void BossState_Strike::MakeBossGrowl()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sound/AncientTree_growl.wav", false);
	return;
}

