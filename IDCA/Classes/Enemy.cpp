#include "pch.h"
#include "Enemy.h"
#include "math.h"


bool Enemy::init(ENEMY::ENEMY_TYPE enemyType, Vec2 initPosition)
{
	if (!Sprite::init())
	{
		return false;
	}

	return true;
}

void Enemy::update(const float deltaTime)
{
	m_pState->runState(this, deltaTime);
	return;
}

// �÷��̾���� �Ÿ��� ���Ͽ� m_DistanceFromPlayer�� �������ش�.
void Enemy::CalDistanceFromPlayer()
{
	auto x = getPlayerPosition().x - m_pSprite->getPosition().x;
	auto y = getPlayerPosition().y - m_pSprite->getPosition().y;

	setDistanceFromPlayer(abs(sqrt(x * x + y * y)));

	return;
}

// Enemy�� Origin�� �Ÿ��� ���Ͽ� m_DistanceFromOrigin�� ����.
void Enemy::CalDistanceFromOrigin()
{
	auto originPoint = getOrigin();
	auto x = originPoint.x - m_pSprite->getPosition().x;
	auto y = originPoint.y - m_pSprite->getPosition().y;

	setDistanceFromOrigin(abs(sqrt(x * x + y * y)));

	return;
}



// Delta ���� �޾� ��������Ʈ�� �����̴� �Լ�.
void Enemy::move(const float deltaTime)
{
	auto deltaX = getUnitVec().x * getMoveSpeed() * deltaTime;
	auto deltaY = getUnitVec().y * getMoveSpeed() * deltaTime;

	auto currentX = m_pSprite->getPositionX();
	auto currentY = m_pSprite->getPositionY();

	m_pSprite->setPosition(currentX + deltaX, currentY + deltaY);
	return;
}

// Origin���� ���ϴ� UnitVec�� ���ϴ� �Լ�.
void Enemy::CalUnitVecToOrigin()
{
	if (!getDistanceFromOrigin())
	{
		return;
	}

	auto distanceFromOrigin = getDistanceFromOrigin();
	auto origin = getOrigin();

	auto deltaX = origin.x - m_pSprite->getPosition().x;
	auto deltaY = origin.y - m_pSprite->getPosition().y;

	Vec2 unitVecToOrigin(deltaX / distanceFromOrigin, deltaY / distanceFromOrigin);
	setUnitVec(unitVecToOrigin);
	return;
}

// �÷��̾�� ���ϴ� UnitVec�� ���ϴ� �Լ�.
void Enemy::CalUnitVecToPlayer()
{
	if (!getDistanceFromPlayer())
	{
		return;
	}
	auto distanceFromPlayer = getDistanceFromPlayer();

	auto deltaX = getPlayerPosition().x - m_pSprite->getPosition().x;
	auto deltaY = getPlayerPosition().y - m_pSprite->getPosition().y;

	Vec2 unitVecToPlayer(deltaX / distanceFromPlayer, deltaY / distanceFromPlayer);
	setUnitVec(unitVecToPlayer);
	return;
}

