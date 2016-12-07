#include "pch.h"
#include "Enemy.h"
#include "math.h"
#include "ManageEnemyMove.h"
#include "AnimationMaker.h"
#include "EnemyState_Approach.h"
#include "EnemyState_Attack.h"
#include "EnemyState_Return.h"
#include "EnemyState_Search.h"
#include "EnemyState_Waiting.h"


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
	DecideWhatIsCurrentAnimation();
	m_pState->runState(this, deltaTime);
	CalDirection();
	CalDistanceFromPlayer();
	CalDistanceFromOrigin();

	CatchStateAndDirection();
	return;
}

// �÷��̾���� �Ÿ��� ���Ͽ� m_DistanceFromPlayer�� �������ش�.
void Enemy::CalDistanceFromPlayer()
{
	auto x = getPlayerPosition().x - this->getPosition().x;
	auto y = getPlayerPosition().y - this->getPosition().y;

	setDistanceFromPlayer(abs(sqrt(x * x + y * y)));

	return;
}

// Enemy�� Origin�� �Ÿ��� ���Ͽ� m_DistanceFromOrigin�� ����.
void Enemy::CalDistanceFromOrigin()
{
	auto originPoint = getOrigin();
	auto x = originPoint.x - this->getPosition().x;
	auto y = originPoint.y - this->getPosition().y;

	setDistanceFromOrigin(abs(sqrt(x * x + y * y)));

	return;
}



// Delta ���� �޾� ��������Ʈ�� �����̴� �Լ�.
void Enemy::MoveEnemy(const float deltaTime)
{
	auto position = m_pManageEnemyMove->update(this->getPosition(), getTranslatedUnitVec(), getMapPointer(), deltaTime, this);
	this->setPosition(position);
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

	auto deltaX = origin.x - this->getPosition().x;
	auto deltaY = origin.y - this->getPosition().y;

	Vec2 unitVecToOrigin(deltaX / distanceFromOrigin, deltaY / distanceFromOrigin);
	setUnitVec(unitVecToOrigin);
	TranslateUnitVec();
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

	auto deltaX = getPlayerPosition().x - this->getPosition().x;
	auto deltaY = getPlayerPosition().y - this->getPosition().y;

	Vec2 unitVecToPlayer(deltaX / distanceFromPlayer, deltaY / distanceFromPlayer);
	setUnitVec(unitVecToPlayer);
	TranslateUnitVec();
	return;
}

// UnitVec�� Direction���� �ٲپ��ִ� �Լ�.
void Enemy::CalDirection()
{
	if (!getTranslatedUnitVec().x || !getTranslatedUnitVec().y)
	{
		int dx = getTranslatedUnitVec().x;
		int dy = getTranslatedUnitVec().y;

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
	int x = 0;
	int y = 0;
	// TODO :: �����ϴ� ���� �� ������ ����.

	if (abs(getUnitVec().x) > 0.01)
	{
		x = (getUnitVec().x > 0) ? 1 : -1;
	}
	else
	{
		x = 0;
	}

	if (abs(getUnitVec().y) > 0.01)
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


void Enemy::CatchStateAndDirection()
{
	// State Catch
	setBeforeState(getState());
	
	// Direction Catch
	setBeforeDirection(getDirection());
}

void Enemy::Stop()
{
	if (IsStopContinued())
	{
		return;
	}
	m_pAnimationMaker->SetAnimationStop();
	auto Sprite = m_pAnimationMaker->AddAnimation(getDirection());

	return;
}

bool Enemy::IsStopContinued()
{
	if (m_pAnimationMaker->IsAnimationContinued() == STATE::STOP
		&& (getBeforeDirection() == getDirection())
		&& (getBeforeState() == getState()))
	{
		return true;
	}

	return false;
}

void Enemy::Move()
{
	if (IsMoveContinued())
	{
		return;
	}
	m_pAnimationMaker->SetAnimationMove();
	auto Sprite = m_pAnimationMaker->AddAnimation(getDirection());

	return;
}

bool Enemy::IsMoveContinued()
{
	if (m_pAnimationMaker->IsAnimationContinued() == STATE::MOVE
		&& (getBeforeDirection() == getDirection())
		&& (getBeforeState() == getState()))
	{
		return true;
	}

	return false;
}

void Enemy::Attack()
{
	if (IsAttackContinued())
	{
		return;
	}
	m_pAnimationMaker->SetAnimationAttack();
	auto Sprite = m_pAnimationMaker->AddAnimation(getDirection());

	return;
}

bool Enemy::IsAttackContinued()
{
	if (m_pAnimationMaker->IsAnimationContinued() == STATE::ATTACK
		&& (getBeforeDirection() == getDirection())
		&& (getBeforeState() == getState()))
	{
		return true;
	}

	return false;
}

void Enemy::DecideWhatIsCurrentAnimation()
{
	// TODO :: �Լ� �����ͷ� �ڵ鸵�ϱ�.
	auto currentStateType = getState()->returnStateNumber();
	if (currentStateType == ENEMY_STATE_TYPE::APPROACHING
		|| currentStateType == ENEMY_STATE_TYPE::RETURN)
	{
		Move();
	}
	else if (currentStateType == ENEMY_STATE_TYPE::ATTACKING)
	{
		Attack();
	}
	else if (currentStateType == ENEMY_STATE_TYPE::SEARCHING
		|| currentStateType == ENEMY_STATE_TYPE::WAITING)
	{
		Stop();
	}
	
	return;
}
