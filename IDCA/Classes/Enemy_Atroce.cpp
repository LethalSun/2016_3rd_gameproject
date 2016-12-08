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


	this->setPosition(initPosition);
	setSearchingRange(400.f);
	setChasingRange(500.f);
	setAttackRange(150.f);
	setMoveSpeed(2.f);

	setIsAttackedOnce(false);
	setIsEnemyPreemptive(true);
	setOrigin(initPosition);
	setAttackSound("Sound/Atroce_swing.mp3");

	// AnimationMaker ¼¼ÆÃ.
	m_pAnimationMaker = AnimationMaker::create("Atroce", ".png");
	addChild(m_pAnimationMaker);
	m_pAnimationMaker->SetAnimationStop();
	m_pAnimationMaker->AddAnimation(getDirection());

	changeState<EnemyState_Search>();

	return true;
}