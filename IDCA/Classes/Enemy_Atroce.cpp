#include "pch.h"
#include "Enemy_Atroce.h"
#include "EnemyState_Search.h"
#include "AnimationMaker.h"

const float Atroce_SearchingRange = 400.f;
const float Atroce_ChasingRange = 500.f;
const float Atroce_AttackRange = 100.f;
const float Atroce_MoveSpeed = 2.f;
const float Atroce_StiffTime = 0.6f;

const char Atroce_AttackSound[] = "Sound/Atroce_swing.mp3";
const char Atroce_Name[] = "Atroce";
const char Atroce_Extention[] = ".png";

bool Enemy_Atroce::init(const Vec2 initPosition)
{
	if (!Enemy::init(initPosition))
	{
		return false;
	}

	setSearchingRange(Atroce_SearchingRange);
	setChasingRange(Atroce_ChasingRange);
	setAttackRange(Atroce_AttackRange);
	setMoveSpeed(Atroce_MoveSpeed);
	setMaxHP(ATROCE_MAX_HP);
	setStiffTime(Atroce_StiffTime);

	auto AttackRangeAtroce = Vec2(ATROCE_ATTACK_RANGE, ATROCE_ATTACK_RANGE);
	setAttackRangeForCollide(AttackRangeAtroce);

	auto BodyRangeAtroce = Vec2(ATROCE_BODY_RANGE_X, ATROCE_BODY_RANGE_Y);
	setBodyRangeForCollide(BodyRangeAtroce);

	setHP(ATROCE_MAX_HP);
	setDamage(ATROCE_ATTACK_DAMAGE);

	setIsAttackedOnce(false);
	setIsEnemyPreemptive(true);
	setAttackSound(Atroce_AttackSound);

	// AnimationMaker ¼¼ÆÃ.
	m_pAnimationMaker = AnimationMaker::create(Atroce_Name, Atroce_Extention);
	addChild(m_pAnimationMaker);
	m_pAnimationMaker->SetAnimationStop();
	m_pAnimationMaker->AddAnimation(getDirection());

	changeState<EnemyState_Search>();
	setBeforeState(getState());

	return true;
}