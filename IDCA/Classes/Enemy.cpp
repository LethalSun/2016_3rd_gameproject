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

// 플레이어와의 거리를 구하여 m_DistanceFromPlayer에 세팅해준다.
void Enemy::CalDistanceFromPlayer()
{
	auto x = getPlayerPosition().x - m_pSprite->getPosition().x;
	auto y = getPlayerPosition().y - m_pSprite->getPosition().y;

	setDistanceFromPlayer(abs(sqrt(x * x + y * y)));

	return;
}

// Enemy와 Origin의 거리를 구하여 m_DistanceFromOrigin에 세팅.
void Enemy::CalDistanceFromOrigin()
{
	auto originPoint = getOrigin();
	auto x = originPoint.x - m_pSprite->getPosition().x;
	auto y = originPoint.y - m_pSprite->getPosition().y;

	setDistanceFromOrigin(abs(sqrt(x * x + y * y)));

	return;
}



// Delta 값을 받아 스프라이트를 움직이는 함수.
void Enemy::move(const float deltaTime)
{
	auto deltaX = getUnitVec().x * getMoveSpeed() * deltaTime;
	auto deltaY = getUnitVec().y * getMoveSpeed() * deltaTime;

	auto currentX = m_pSprite->getPositionX();
	auto currentY = m_pSprite->getPositionY();

	m_pSprite->setPosition(currentX + deltaX, currentY + deltaY);
	return;
}

// Origin에게 향하는 UnitVec를 구하는 함수.
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

// 플레이어에게 향하는 UnitVec을 구하는 함수.
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

