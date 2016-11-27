#include "pch.h"
#include "Enemy_Choco.h"
#include "EnemyState_Search.h"

using namespace ENEMY::CHOCO;

bool Enemy_Choco::init(Vec2 initPosition)
{
	if (!Enemy::init(initPosition))
	{
		setOrigin(Vec2(STATIC::visibleSize.width * initPosition.x,
			STATIC::visibleSize.height * initPosition.y));

		return false;
	}

	// 내부 변수값 세팅.
	setSearchingRange	(SEARCHING_RANGE);
	setChasingRange		(CHASING_RANGE);
	setAttackRange		(ATTACK_RANGE);
	setMoveSpeed		(MOVE_SPEED);
	setIsAttackedOnce	(false); 
	setIsHited			(false);

	// Sprite 생성
	m_pSprite = Sprite::create(CHOCO_SPRITE);
	m_pSprite->setPosition(getOrigin());
	addChild(m_pSprite);

	changeState<EnemyState_Search>();

	return true;
}