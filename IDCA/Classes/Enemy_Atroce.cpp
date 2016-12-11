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