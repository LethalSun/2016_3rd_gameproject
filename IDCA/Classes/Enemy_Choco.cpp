#include "pch.h"
#include "Enemy_Choco.h"
#include "EnemyState_Search.h"
#include "Config.h"
#include "AnimationMaker.h"

const float Choco_SearchingRange = 400.f;
const float Choco_ChasingRange = 500.f;
const float Choco_AttackRange = 50.f;
const float Choco_MoveSpeed = 3.5f;

const char Choco_Name[] = "Choco";
const char Choco_Extention[] = ".png";

bool Enemy_Choco::init(const Vec2 initPosition)
{
	if (!Enemy::init(initPosition))
	{
		return false;
	}

	setSearchingRange(Choco_SearchingRange);
	setChasingRange(Choco_ChasingRange);
	setAttackRange(Choco_AttackRange);
	setMoveSpeed(Choco_MoveSpeed);
	setIsAttackedOnce	(false);

	auto AttackRangeChoco = Vec2(CHOCO_ATTACK_RANGE, CHOCO_ATTACK_RANGE);
	setAttackRangeForCollide(AttackRangeChoco);
	auto BodyRangeChoco = Vec2(CHOCO_BODY_RANGE_X, CHOCO_BODY_RANGE_Y);
	setBodyRangeForCollide(BodyRangeChoco);
	setIsAttackedOnce(false);
	setIsEnemyPreemptive(false);

	setHP(CHOCO_MAX_HP);
	setMaxHP(CHOCO_MAX_HP);
	setDamage(CHOCO_ATTACK_DAMAGE);


	// AnimationMaker ����.
	m_pAnimationMaker = AnimationMaker::create(Choco_Name, Choco_Extention);
	addChild(m_pAnimationMaker);
	m_pAnimationMaker->SetAnimationStop();
	m_pAnimationMaker->AddAnimation(getDirection());

	changeState<EnemyState_Search>();
	setBeforeState(getState());

	scheduleUpdate();
	return true;
}
