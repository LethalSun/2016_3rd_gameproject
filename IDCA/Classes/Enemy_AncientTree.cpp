#include "pch.h"
#include "Enemy_AncientTree.h"
#include "EnemyState_Search.h"
#include "AnimationMaker.h"


bool Enemy_AncientTree::init(const Vec2 initPosition)
{
	if (!Enemy::init(initPosition))
	{
		return false;
	}

	setSearchingRange(ANCIENT_TREE_SEARCHING_RANGE);
	setChasingRange(ANCIENT_TREE_CHASING_RANGE);
	setAttackRange(ANCIENT_TREE_ATTACKING_RANGE);
	setMaxHP(ANCIENT_TREE_MAX_HP);
	setHP(ANCIENT_TREE_MAX_HP);
	setDamage(ANCIENT_TREE_DAMAGE);
	setMoveSpeed(ANCIENT_TREE_MOVE_SPEED);
	setStiffTime(ANCIENT_TREE_STIFF_TIME);
	setSummonCoolTime(ANCIENT_TREE_SUMMON_COOL_TIME);
	setAttackFrequency(ANCIENT_TREE_ATTACK_FREQUENCY_INIT);

	auto BodyRange = Vec2(ANCIENT_TREE_BODY_RANGE_X, ANCIENT_TREE_BODY_RANGE_Y);
	setBodyRangeForCollide(BodyRange);

	setIsAttackedOnce(false);
	setIsEnemyPreemptive(true);
	setAttackNumber(0);

	// Sound ����
	setAttackSound(ANCIENT_TREE_ATTACK_SOUND);
	setHitedSound(ANCIENT_TREE_HITED_SOUND);
	setDyingSound(ANCIENT_TREE_DYING_SOUND);

	// AnimationMaker ����.
	m_pAnimationMaker = AnimationMaker::create(ANCIENT_TREE_NAME, ANCIENT_TREE_FILE_EXTENSION);
	addChild(m_pAnimationMaker);
	m_pAnimationMaker->SetAnimationStop();
	m_pAnimationMaker->AddAnimation(getDirection());

	changeState<EnemyState_Search>();
	setBeforeState(getState());

	scheduleUpdate();
	return true;
}


