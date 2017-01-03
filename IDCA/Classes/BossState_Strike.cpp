#include "pch.h"
#include "Enemy.h"
#include "SimpleAudioEngine.h"
#include "BossState_Strike.h"
#include "BossState_Attack.h"
#include "AnimationMaker.h"
#include "Tentacle.h"

// Strike�� ���۵� ��, ���� Ŀ���鼭 �Ӱ� ���Ͽ� �÷��̾�� ���.
void BossState_Strike::startState(Enemy* enemy)
{
	// Ŀ���� �Ӿ����� �׼� ����.
	auto biggerAction = ScaleTo::create(ANCIENT_TREE_STRIKE_RELEASE_TIME, ANCIENT_TREE_STRIKE_BIGGER_SCALE);
	auto redAction = TintBy::create(ANCIENT_TREE_STRIKE_RELEASE_TIME, 0, -255, -255);
	auto waitingAction = Spawn::create(biggerAction, redAction, nullptr);

	// ���� �����ϴ� �׼� ����.
	auto smallerAction = ScaleTo::create(ANCIENT_TREE_STRIKE_SHRINK_TIME, ANCIENT_TREE_STRIKE_NORMAL_SCALE);
	auto recoveryAction = TintBy::create(ANCIENT_TREE_STRIKE_SHRINK_TIME, 0, 255, 255);
	auto shrinkAction = Spawn::create(smallerAction, recoveryAction, nullptr);

	// Ŀ���ٰ� �Ҹ��� ���鼭 �ٽ� �۾����� ������ �׼� ����.
	auto callFunc = CallFunc::create(CC_CALLBACK_0(BossState_Strike::MakeBossGrowl, this));
	auto seqAction = Sequence::create(waitingAction, callFunc, shrinkAction, nullptr);
	enemy->m_pAnimationMaker->GetSprite()->runAction(seqAction);
	
	m_AcculmulateTime = 0.f;
	return;
}

// ���� �ð��� ���� �ð� �̻��� �Ǹ� Strike�� �����ϰ� �ٽ� Attack ���·� ����. 
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

// ������ Strike ���� �Ҹ��� ���� �Լ�.
void BossState_Strike::MakeBossGrowl()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(ANCIENT_TREE_GROWL, false);
	return;
}

