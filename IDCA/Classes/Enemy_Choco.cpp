#include "pch.h"
#include "Enemy_Choco.h"
#include "EnemyState_Search.h"

using namespace ENEMY::CHOCO;

bool Enemy_Choco::init(ENEMY::ENEMY_TYPE enemyType, Vec2 initPosition)
{
	if (!Enemy::init(enemyType, initPosition))
	{
		return false;
	}

	// ���� ������ ����.
	setSearchingRange	(SEARCHING_RANGE);
	setChasingRange		(CHASING_RANGE);
	setAttackRange		(ATTACK_RANGE);
	setOrigin			(Vec2(STATIC::visibleSize.width * INIT_WIDTH, STATIC::visibleSize.height * INIT_HEIGHT));
	setMoveSpeed		(MOVE_SPEED);
	setIsAttackedOnce	(false); 
	setIsHited			(false);

	// Sprite ����
	m_pSprite = Sprite::create(CHOCO_SPRITE);
	m_pSprite->setPosition(getOrigin());
	addChild(m_pSprite);

	changeState<EnemyState_Search>();

	return true;
}

// m_pSprite�� ���� ��������Ʈ�� ��ȯ.
void Enemy_Choco::SetSpriteToAttack()
{
	m_pSprite = Sprite::create(CHOCO_ATTACK_SPRITE);
	addChild(m_pSprite);
	return;
}

// m_pSprite�� �ϻ� ��������Ʈ�� ��ȯ.
void Enemy_Choco::SetSpriteToCommon()
{
	m_pSprite = Sprite::create(CHOCO_SPRITE);
	addChild(m_pSprite);
	return;
}

