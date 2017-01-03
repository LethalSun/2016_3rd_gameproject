#include "pch.h"
#include "Enemy_Choco.h"
#include "EnemyState_Search.h"
#include "Config.h"
#include "AnimationMaker.h"



bool Enemy_Choco::init(const Vec2 initPosition)
{
	if (!Enemy::init(initPosition))
	{
		return false;
	}

	setSearchingRange(CHOCO_SEARCHING_RANGE);
	setChasingRange(CHOCO_CHASING_RANGE);
	setAttackRange(CHOCO_ATTACKING_RANGE);
	setMoveSpeed(CHOCO_MOVE_SPEED);
	setIsAttackedOnce(false);
	setStiffTime(CHOCO_STIFF_TIME);

	auto AttackRangeChoco = Vec2(CHOCO_ATTACK_RANGE, CHOCO_ATTACK_RANGE);
	setAttackRangeForCollide(AttackRangeChoco);
	auto BodyRangeChoco = Vec2(CHOCO_BODY_RANGE_X, CHOCO_BODY_RANGE_Y);
	setBodyRangeForCollide(BodyRangeChoco);
	setIsAttackedOnce(false);
	setIsEnemyPreemptive(true);

	setHP(CHOCO_MAX_HP);
	setMaxHP(CHOCO_MAX_HP);
	setDamage(CHOCO_ATTACK_DAMAGE);

	// Sound 세팅
	setAttackSound(CHOCO_ATTACK_SOUND);
	setAttackSoundExtension(CHOCO_ATTACK_SOUND_EXTENSION);
	setHitedSound(CHOCO_HITED_SOUND);
	setDyingSound(CHOCO_DYING_SOUND);

	// AnimationMaker 세팅.
	m_pAnimationMaker = AnimationMaker::create(CHOCO_NAME, CHOCO_EXTENSION);
	addChild(m_pAnimationMaker);
	m_pAnimationMaker->SetAnimationStop();
	m_pAnimationMaker->AddAnimation(getDirection());

	changeState<EnemyState_Search>();
	setBeforeState(getState());


	positiionOfHp = Vec2(POSITIONOFHP_CHOCO_X, POSITIONOFHP_CHOCO_Y);
	sizeOfHp_x = SIZEOFHP_X_CHOCO;
	sizeOfHp_y = SIZEOFHP_Y_CHOCO;

	scheduleUpdate();
	return true;
}
