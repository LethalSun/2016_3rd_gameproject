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
	setIsEnemyPreemptive(false);


	// AnimationMaker ¼¼ÆÃ.
	m_pAnimationMaker = AnimationMaker::create(Choco_Name, Choco_Extention);
	addChild(m_pAnimationMaker);
	m_pAnimationMaker->SetAnimationStop();
	m_pAnimationMaker->AddAnimation(getDirection());

	changeState<EnemyState_Search>();
	setBeforeState(getState());

	return true;
}