#include "pch.h"
#include "Enemy.h"
#include "math.h"
#include "ManageEnemyMove.h"


bool Enemy::init(const Vec2 initPosition)
{
	if (!Node::init())
	{
		return false;
	}

	setUnitVec(Vec2(0, 0));
	setDirection(DIRECTION::BOTTOM);
	m_pManageEnemyMove = ManageEnemyMove::create();
	setIsAttackedOnce(false);

	return true;
}

void Enemy::update(const float deltaTime)
{
	m_pState->runState(this, deltaTime);
	CalDirection();
	CalDistanceFromPlayer();
	CalDistanceFromOrigin();

	return;
}

// 플레이어와의 거리를 구하여 m_DistanceFromPlayer에 세팅해준다.
void Enemy::CalDistanceFromPlayer()
{
	auto x = getPlayerPosition().x - this->getPosition().x;
	auto y = getPlayerPosition().y - this->getPosition().y;

	setDistanceFromPlayer(abs(sqrt(x * x + y * y)));

	return;
}

// Enemy와 Origin의 거리를 구하여 m_DistanceFromOrigin에 세팅.
void Enemy::CalDistanceFromOrigin()
{
	auto originPoint = getOrigin();
	auto x = originPoint.x - this->getPosition().x;
	auto y = originPoint.y - this->getPosition().y;

	setDistanceFromOrigin(abs(sqrt(x * x + y * y)));

	return;
}



// Delta 값을 받아 스프라이트를 움직이는 함수.
void Enemy::move(const float deltaTime)
{
	auto position = m_pManageEnemyMove->update(this->getPosition(), getTranslatedUnitVec(), getMapPointer(), deltaTime,this);
	this->setPosition(position);
	/*
	auto deltaX = getUnitVec().x * getMoveSpeed() * deltaTime;
	auto deltaY = getUnitVec().y * getMoveSpeed() * deltaTime;

	auto currentX = this->getPositionX();
	auto currentY = this->getPositionY();

	this->setPosition(currentX + deltaX, currentY + deltaY);
	*/
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

	auto deltaX = origin.x - this->getPosition().x;
	auto deltaY = origin.y - this->getPosition().y;

	Vec2 unitVecToOrigin(deltaX / distanceFromOrigin, deltaY / distanceFromOrigin);
	setUnitVec(unitVecToOrigin);
	TranslateUnitVec();
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

	auto deltaX = getPlayerPosition().x - this->getPosition().x;
	auto deltaY = getPlayerPosition().y - this->getPosition().y;

	Vec2 unitVecToPlayer(deltaX / distanceFromPlayer, deltaY / distanceFromPlayer);
	setUnitVec(unitVecToPlayer);
	TranslateUnitVec();
	return;
}

// UnitVec을 Direction으로 바꾸어주는 함수.
void Enemy::CalDirection()
{
	if (!getUnitVec().x || !getUnitVec().y)
	{
		int dx = 0;
		int dy = 0;
		if (!getUnitVec().x)
		{
			dx = (getUnitVec().x > 0) ? 1 : -1;
		}
		if (!getUnitVec().y)
		{
			dy = (getUnitVec().y > 0) ? 1 : -1;
		}

		if ((dx == 0) && (dy == 1))
		{
			setDirection(DIRECTION::TOP);
		}
		else if ((dx == 1) && (dy == 1))
		{
			setDirection(DIRECTION::TOP_RIGHT);
		}
		else if ((dx == 1) && (dy == 0))
		{
			setDirection(DIRECTION::RIGHT);
		}
		else if ((dx == 1) && (dy == -1))
		{
			setDirection(DIRECTION::BOTTOM_RIGHT);
		}
		else if ((dx == 0) && (dy == -1))
		{
			setDirection(DIRECTION::BOTTOM);
		}
		else if ((dx == -1) && (dy == -1))
		{
			setDirection(DIRECTION::BOTTOM_LEFT);
		}
		else if ((dx == -1) && (dy == 0))
		{
			setDirection(DIRECTION::LEFT);
		}
		else if ((dx == -1) && (dy == 1))
		{
			setDirection(DIRECTION::TOP_LEFT);
		}

	}
	return;
}


void Enemy::TranslateUnitVec()
{
	int x, y;

	if (getUnitVec().x != 0)
	{
		x = (getUnitVec().x > 0) ? 1 : -1;
	}
	else
	{
		x = 0;
	}

	if (getUnitVec().y != 0)
	{
		y = (getUnitVec().y > 0) ? 1 : -1;
	}
	else
	{
		y = 0;
	}

	setTranslatedUnitVec(Vec2(x, y));
	return;
}