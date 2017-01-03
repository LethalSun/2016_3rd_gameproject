#include "pch.h"
#include "Enemy_AncientTree.h"
#include "EnemyState_Search.h"
#include "AnimationMaker.h"

const float AncientTree_SearchingRange = 400.f;
const float AncientTree_ChansingRange = 400.f;
const float AncientTree_AttackRange = 500.f;
const float AncientTree_MoveSpeed = 5.f;
const float AncientTree_StiffTime = 0.0f;
const float AncientTree_SummonCoolTime = 5.f;
const float AnicnetTree_AttackFrequencyInitial = 1.4f;

const char AncientTree_Name[] = "AncientTree";
const char AncientTree_Extension[] = ".png";
const char AncientTree_AttackSound[] = "Sound/AncientTree_hitGround.wav";
const char AncientTree_HitedSound[] = "Sound/AncientTree_hited.aiff";
const char AncientTree_DyingSound[] = "Sound/AncientTree_dying.wav";

bool Enemy_AncientTree::init(const Vec2 initPosition)
{
	if (!Enemy::init(initPosition))
	{
		return false;
	}

	setSearchingRange(AncientTree_SearchingRange);
	setChasingRange(AncientTree_ChansingRange);
	setAttackRange(AncientTree_AttackRange);
	setMaxHP(ANCIENT_TREE_MAX_HP);
	setHP(ANCIENT_TREE_MAX_HP);
	setDamage(ANCIENT_TREE_DAMAGE);
	setMoveSpeed(AncientTree_MoveSpeed);
	setStiffTime(AncientTree_StiffTime);
	setSummonCoolTime(AncientTree_SummonCoolTime);
	setAttackFrequency(AnicnetTree_AttackFrequencyInitial);

	auto BodyRange = Vec2(ANCIENT_TREE_BODY_RANGE_X, ANCIENT_TREE_BODY_RANGE_Y);
	setBodyRangeForCollide(BodyRange);

	setIsAttackedOnce(false);
	setIsEnemyPreemptive(true);
	setAttackNumber(0);

	// Sound 세팅
	setAttackSound(AncientTree_AttackSound);
	setHitedSound(AncientTree_HitedSound);
	setDyingSound(AncientTree_DyingSound);

	// AnimationMaker 세팅.
	m_pAnimationMaker = AnimationMaker::create(AncientTree_Name, AncientTree_Extension);
	addChild(m_pAnimationMaker);
	m_pAnimationMaker->SetAnimationStop();
	m_pAnimationMaker->AddAnimation(getDirection());

	changeState<EnemyState_Search>();
	setBeforeState(getState());

	positiionOfHp = Vec2(131, 150);
	sizeOfHp_x = 0.5;
	sizeOfHp_y = 0.5;

	scheduleUpdate();
	return true;
}


