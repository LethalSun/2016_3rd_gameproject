#include "pch.h"
#include "Enemy_Atroce.h"
#include "EnemyState_Search.h"
#include "AnimationMaker.h"

bool Enemy_Atroce::init(const Vec2 initPosition)
{
	if (!Enemy::init(initPosition))
	{
		return false;
	}

	setSearchingRange(400.f);
	setChasingRange(500.f);
	setAttackRange(100.f);
	setMoveSpeed(2.f);

	auto AttackRangeAtroce = Vec2(ATROCE_ATTACK_RANGE, ATROCE_ATTACK_RANGE);
	setAttackRangeForCollide(AttackRangeAtroce);

	auto BodyRangeAtroce = Vec2(ATROCE_BODY_RANGE_X, ATROCE_BODY_RANGE_Y);
	setBodyRangeForCollide(BodyRangeAtroce);

	setHP(ATROCE_MAX_HP);
	setDamage(ATROCE_ATTACK_DAMAGE);

	setIsAttackedOnce(false);
	setIsEnemyPreemptive(true);
	setAttackSound("Sound/Atroce_swing.mp3");

	// AnimationMaker ¼¼ÆÃ.
	m_pAnimationMaker = AnimationMaker::create("Atroce", ".png");
	addChild(m_pAnimationMaker);
	m_pAnimationMaker->SetAnimationStop();
	m_pAnimationMaker->AddAnimation(getDirection());

	changeState<EnemyState_Search>();
	setBeforeState(getState());

	return true;
}