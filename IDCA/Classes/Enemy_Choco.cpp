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

	// Config �̱��� Ŭ���� ȣ��.
	//m_pConfig->getInstance();

	this->setPosition(initPosition);
	setSearchingRange(400.f);
	setChasingRange(500.f);
	setAttackRange(150.f);
	setMoveSpeed(200.f);
	// ���� ������ ����.
	/*setSearchingRange	(m_pConfig->getChocoSearchingRange());
	setChasingRange		(m_pConfig->getChocoChasingRange());
	setAttackRange		(m_pConfig->getChocoAttackRange());
	setMoveSpeed		(m_pConfig->getChocoMoveSpeed());*/
	setIsAttackedOnce	(false);
	setIsEnemyPreemptive(false);
	setOrigin(Vec2(initPosition.x, initPosition.y));


	// AnimationMaker ����.
	m_pAnimationMaker = AnimationMaker::create("Choco", ".png");
	addChild(m_pAnimationMaker);
	m_pAnimationMaker->SetAnimationStop();
	m_pAnimationMaker->AddAnimation(getDirection());

	changeState<EnemyState_Search>();

	return true;
}