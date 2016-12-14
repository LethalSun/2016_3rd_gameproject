#include "pch.h"
#include "Enemy.h"
#include "SimpleAudioEngine.h"
#include "math.h"
#include "ManageEnemyMove.h"
#include "AnimationMaker.h"
#include "EnemyState_Approach.h"
#include "EnemyState_Attack.h"
#include "EnemyState_Return.h"
#include "EnemyState_Search.h"
#include "EnemyState_Waiting.h"

const Vec2 ZERO = Vec2(0.f, 0.f);
const float IgnoreMoveRange = 0.01f;


bool Enemy::init(const Vec2 initPosition)
{
	if (!Node::init())
	{
		return false;
	}

	m_pManageEnemyMove = ManageEnemyMove::create();
	addComponent(m_pManageEnemyMove);
	m_pLabel = Label::create();
	m_pLabel->setColor(ccc3(255, 0, 0));
	addChild(m_pLabel, 5);

	setPosition(initPosition);
	setOrigin(initPosition);
	setUnitVecToPlayer(ZERO);
	setUnitVecToOrigin(ZERO);
	setTranslatedUnitVec(ZERO);
	setBeforeDirection(DIRECTION::BOTTOM);
	setDirection(DIRECTION::BOTTOM);
	setIsAttackedOnce(false);

	return true;
}

void Enemy::update(const float deltaTime)
{
	CatchStateAndDirection();
	CalDistanceFromPlayer();
	CalDistanceFromOrigin();

	m_pState->runState(this, deltaTime);

	CalculateBodyAnchorPoint();

	//MakeBox(m_BodyAnchorPointForDebugBox, m_BodyRangeForCollide, m_GreenBoxTag);

	char buf[255];
	sprintf(buf, "HP: %d", getHP());
	m_pLabel->setString(buf);
	//CCLOG(buf);

	DecideWhatIsCurrentAnimation();
	if (!IsEnemyMaxHp())
	{
		setIsAttackedOnce(false);
	}
	
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
void Enemy::MoveEnemy(const float deltaTime)
{
	auto position = m_pManageEnemyMove->update(this->getPosition(), getTranslatedUnitVec(), getMapPointer(), deltaTime, this);

	this->setPosition(position);
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
	setUnitVecToOrigin(unitVecToOrigin);
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
	setUnitVecToPlayer(unitVecToPlayer);
	return;
}

// UnitVec을 Direction으로 바꾸어주는 함수.
void Enemy::CalDirection(Vec2 InputUnitVec)
{
	int dx = InputUnitVec.x;
	int dy = InputUnitVec.y;

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

	return;
}

void Enemy::TranslateUnitVec(Vec2 InputUnitVec)
{
	int x = 0;
	int y = 0;

	if (abs(InputUnitVec.x) > IgnoreMoveRange)
	{
		x = (InputUnitVec.x > 0) ? 1 : -1;
	}
	else
	{
		x = 0;
	}

	if (abs(InputUnitVec.y) > IgnoreMoveRange) 
	{
		y = (InputUnitVec.y > 0) ? 1 : -1;
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

void Enemy::CalculateAttackAnchorPoint()
{
	//디버그 박스용 어택포인트
	auto position = Vec2(0.f, 0.f);

	auto bodyPositionX = position.x;
	auto bodyPositionY = position.y;

	auto offsetX = (m_BodyRangeForCollide.x / 2) + (m_AttackRangeForCollide.x / 2);
	auto deltaX = m_TranslatedUnitVec.x * offsetX;
	auto attackPostionX = bodyPositionX + deltaX;

	auto offsetY = (m_BodyRangeForCollide.y / 2) + (m_AttackRangeForCollide.y / 2);
	auto deltaY = m_TranslatedUnitVec.y * offsetY;
	auto attackPostionY = bodyPositionY + deltaY;

	m_AttackAnchorPointForDebugBox = Vec2(attackPostionX, attackPostionY);

	//실제 충돌용 어택 포인트
	position = getPosition();
	bodyPositionX = position.x;
	bodyPositionY = position.y;

	attackPostionX = bodyPositionX + deltaX;
	attackPostionY = bodyPositionY + deltaY;

	m_AttackAnchorPoint = Vec2(attackPostionX, attackPostionY);
}

void Enemy::CalculateBodyAnchorPoint()
{
	//디버그 박스용 피격포인트
	m_BodyAnchorPointForDebugBox = Vec2(0.f, 0.f);

	//실제 충돌용 피격포인트
	m_BodyAnchorPoint = getPosition();
}

void Enemy::MakeBox(Vec2 position, Vec2 boxInfo, const int tag)
{
	if (getChildByTag(tag) != nullptr)
	{
		removeChildByTag(tag);
	}
	Vec2 vertex[2] = { Vec2(position.x - boxInfo.x / 2,position.y - boxInfo.y / 2),
		Vec2(position.x + boxInfo.x / 2,position.y + boxInfo.y / 2) };
	auto box = DrawNode::create();
	if (tag == GREEN_BOX_TAG)
	{
		box->drawRect(vertex[0], vertex[1], Color4F(0.0f, 1.0f, 0.0f, 1.0f));
	}
	else if (tag == RED_BOX_TAG)
	{
		box->drawRect(vertex[0], vertex[1], Color4F(1.0f, 0.0f, 0.0f, 1.0f));
	}

	addChild(box, 0, tag);
}

bool Enemy::Stop()
{
	if (IsStopContinued())
	{
		return false;
	}
	m_pAnimationMaker->SetAnimationStop();
	auto Sprite = m_pAnimationMaker->AddAnimation(getDirection());

	return true;
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

bool Enemy::Move()
{
	if (IsMoveContinued())
	{
		return false;
	}
	m_pAnimationMaker->SetAnimationMove();
	auto Sprite = m_pAnimationMaker->AddAnimation(getDirection());

	return true;
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

bool Enemy::Attack()
{
	if (IsAttackContinued())
	{
		return false;
	}
	m_pAnimationMaker->SetAnimationAttack();
	auto Sprite = m_pAnimationMaker->AddAnimation(getDirection());
	//int attackSound = CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(this->getAttackSound(), false);

	CalculateAttackAnchorPoint();
	//MakeBox(m_AttackAnchorPointForDebugBox, m_AttackRangeForCollide, m_RedBoxTag);

	return true;
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
	// TODO :: 함수 포인터로 핸들링하기.
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

	//Question :: 함수 포인터 질문하기.
	//bool(*StateHandler[ENEMY_STATE_TYPE::STATE_NUM])() = { Move, };
	

bool Enemy::IsEnemyMaxHp()
{
	if (getHP() == getMaxHP())
	{
		return true;
	}

	return false;
}
