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

	setSearchingRange(ATROCE_SEARCHING_RANGE);
	setChasingRange(ATROCE_CHASING_RANGE);
	setAttackRange(ATROCE_ATTACKING_RANGE);
	setMoveSpeed(ATROCE_MOVE_SPEED);
	setMaxHP(ATROCE_MAX_HP);
	setStiffTime(ATROCE_STIFF_TIME);

	auto AttackRangeAtroce = Vec2(ATROCE_ATTACK_RANGE, ATROCE_ATTACK_RANGE);
	setAttackRangeForCollide(AttackRangeAtroce);

	auto BodyRangeAtroce = Vec2(ATROCE_BODY_RANGE_X, ATROCE_BODY_RANGE_Y);
	setBodyRangeForCollide(BodyRangeAtroce);

	setHP(ATROCE_MAX_HP);
	setDamage(ATROCE_ATTACK_DAMAGE);

	setIsAttackedOnce(false);
	setIsEnemyPreemptive(true);

	// Sound 세팅
	setAttackSound(ATROCE_ATTACK_SOUND);
	setAttackSoundExtension(ATROCE_ATTACK_SOUND_EXTENSION);
	setHitedSound(ATROCE_HITED_SOUND);
	setDyingSound(ATROCE_DYING_SOUND);

	// AnimationMaker 세팅.
	m_pAnimationMaker = AnimationMaker::create(ATROCE_NAME, ATROCE_EXTENSION);
	addChild(m_pAnimationMaker);
	m_pAnimationMaker->SetAnimationStop();
	m_pAnimationMaker->AddAnimation(getDirection());

	changeState<EnemyState_Search>();
	setBeforeState(getState());


	positiionOfHp = Vec2(POSITIONOFHP_ATROCE_X, POSITIONOFHP_ATROCE_Y);
	sizeOfHp_x = SIZEOFHP_X_ATROCE;
	sizeOfHp_y = SIZEOFHP_Y_ATROCE;

	return true;
}