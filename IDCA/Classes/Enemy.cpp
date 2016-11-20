#include "pch.h"
#include "Enemy.h"
#include "math.h"


bool Enemy::init()
{
	if (!Sprite::init())
	{
		return false;
	}

	return true;
}

void Enemy::update(float dt)
{
	m_pState->runState(this, dt);
	return;
}

// 플레이어와의 거리를 구하여 m_DistanceFromPlayer에 세팅해준다.
void Enemy::CalDistanceFromPlayer()
{
	float x = getPlayerPosition().x - m_pSprite->getPosition().x;
	float y = getPlayerPosition().y - m_pSprite->getPosition().y;

	setDistanceFromPlayer(abs(sqrt(x * x + y * y)));

	return;
}

// Enemy와 Origin의 거리를 구하여 m_DistanceFromOrigin에 세팅.
void Enemy::CalDistanceFromOrigin()
{
	Point originPoint = getOrigin();
	float x = originPoint.x - m_pSprite->getPosition().x;
	float y = originPoint.y - m_pSprite->getPosition().y;

	setDistanceFromOrigin(abs(sqrt(x * x + y * y)));

	return;
}


//
//void Enemy::SetSpriteToAttack()
//{
//	return;
//}
//
//void Enemy::SetSpriteToCommon()
//{
//	return;
//}


// Delta 값을 받아 스프라이트를 움직이는 함수.
void Enemy::move(float dt)
{
	float dtX = getUnitVec().x * getMoveSpeed() * dt;
	float dtY = getUnitVec().y * getMoveSpeed() * dt;

	auto currentX = m_pSprite->getPositionX();
	auto currentY = m_pSprite->getPositionY();

	m_pSprite->setPosition(currentX + dtX, currentY + dtY);
	return;
}

// Origin에게 향하는 UnitVec를 구하는 함수.
void Enemy::CalUnitVecToOrigin()
{
	if (!getDistanceFromOrigin())
	{
		return;
	}

	float distanceFromOrigin = getDistanceFromOrigin();
	Vec2 origin = getOrigin();

	float x = origin.x - m_pSprite->getPosition().x;
	float y = origin.y - m_pSprite->getPosition().y;

	Vec2 unitVecToOrigin(x / distanceFromOrigin, y / distanceFromOrigin);
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
	float distanceFromPlayer = getDistanceFromPlayer();

	float x = getPlayerPosition().x - m_pSprite->getPosition().x;
	float y = getPlayerPosition().y - m_pSprite->getPosition().y;

	Vec2 unitVecToPlayer(x / distanceFromPlayer, y / distanceFromPlayer);
	setUnitVec(unitVecToPlayer);
	return;
}

