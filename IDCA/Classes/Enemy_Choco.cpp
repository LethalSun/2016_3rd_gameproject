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

	// Config 싱글톤 클래스 호출.
	//m_pConfig->getInstance();

	this->setPosition(initPosition);
	setSearchingRange(400.f);
	setChasingRange(500.f);
	setAttackRange(50.f);
	setMoveSpeed(3.5f);
	auto AttackRangeChoco = Vec2(CHOCO_ATTACK_RANGE, CHOCO_ATTACK_RANGE);
	setAttackRangeForCollide(AttackRangeChoco);
	auto BodyRangeChoco = Vec2(CHOCO_BODY_RANGE_X, CHOCO_BODY_RANGE_Y);
	setBodyRangeForCollide(BodyRangeChoco);
	// 내부 변수값 세팅.
	/*setSearchingRange	(m_pConfig->getChocoSearchingRange());
	setChasingRange		(m_pConfig->getChocoChasingRange());
	setAttackRange		(m_pConfig->getChocoAttackRange());
	setMoveSpeed		(m_pConfig->getChocoMoveSpeed());*/
	setIsAttackedOnce(false);
	setIsEnemyPreemptive(false);
	setOrigin(Vec2(initPosition.x, initPosition.y));

	setHP(CHOCO_MAX_HP);
	setDamage(CHOCO_ATTACK_DAMAGE);


	// AnimationMaker 세팅.
	m_pAnimationMaker = AnimationMaker::create("Choco", ".png");
	addChild(m_pAnimationMaker);
	m_pAnimationMaker->SetAnimationStop();
	m_pAnimationMaker->AddAnimation(getDirection());

	changeState<EnemyState_Search>();

	return true;
}