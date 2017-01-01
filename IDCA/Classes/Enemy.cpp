#include "pch.h"
#include "Enemy.h"
#include "EnemyManager.h"
#include "SimpleAudioEngine.h"
#include "AudioEngine.h"
#include "math.h"
#include "ManageEnemyMove.h"
#include "AnimationMaker.h"
#include "EnemyState_Approach.h"
#include "EnemyState_Attack.h"
#include "EnemyState_Return.h"
#include "EnemyState_Search.h"
#include "EnemyState_Waiting.h"
#include "EnemyState_BeAttacked.h"
#include "EffectManager.h"

const Vec2 ZERO = Vec2(0.f, 0.f);
const float IgnoreMoveRange = 0.05f;

bool Enemy::init(const Vec2 initPosition)
{
	if (!Node::init())
	{
		return false;
	}

	m_pManageEnemyMove = ManageEnemyMove::create();
	m_pEffectManager = EffectManager::create();
	addChild(m_pEffectManager, 5);
	addComponent(m_pManageEnemyMove);
	m_pLabel = Label::create();
	m_pLabel->setColor(ccc3(255, 0, 0));
	addChild(m_pLabel, 5);

	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(this->getAttackSound());

	setPosition(initPosition);
	setOrigin(initPosition);
	setUnitVecToPlayer(ZERO);
	setUnitVecToOrigin(ZERO);
	setTranslatedUnitVec(ZERO);
	setBeforeDirection(DIRECTION::BOTTOM);
	setDirection(DIRECTION::BOTTOM);
	setIsAttackedOnce(false);
	setFlagBeAttacked(false);
	setIsDead(false);
	setIsSleeping(false);

	return true;
}

void Enemy::update(const float deltaTime)
{
	CatchStateAndDirection();
	CalDistanceFromPlayer();
	CalDistanceFromOrigin();

	m_pState->runState(this, deltaTime);

	CalculateBodyAnchorPoint();

	DecideWhatIsCurrentAnimation();

	MakeHPBox();

	char buf[255];
	sprintf(buf, "state : %d, distance : %f, \n player X : %f, player Y : %f \n unitVec X : %f, unitVec Y : %f", getState()->returnStateNumber(), getDistanceFromPlayer(), getPlayerPosition().x, getPlayerPosition().y, getUnitVecToPlayer().x, getUnitVecToPlayer().y);
	CCLOG(buf);

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
	setUnitVecToOrigin(unitVecToOrigin);
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
	setUnitVecToPlayer(unitVecToPlayer);
	return;
}

// UnitVec�� Direction���� �ٲپ��ִ� �Լ�.
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

// float ������ ���ֺ��͸� �޾Ƽ� int������ ������ �ٲ��ش�.
// IgnoreMoveRange�� ���� ��ŭ�� �����Ͽ� ��鸲�� �������ش�.
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

// Before State�� Direction�� �������ִ� �Լ�.
void Enemy::CatchStateAndDirection()
{
	// State Catch
	setBeforeState(getState());

	// Direction Catch
	setBeforeDirection(getDirection());
}

void Enemy::CalculateAttackAnchorPoint()
{
	//����� �ڽ��� ��������Ʈ
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

	//���� �浹�� ���� ����Ʈ
	position = getPosition();
	bodyPositionX = position.x;
	bodyPositionY = position.y;

	attackPostionX = bodyPositionX + deltaX;
	attackPostionY = bodyPositionY + deltaY;

	m_AttackAnchorPoint = Vec2(attackPostionX, attackPostionY);
}

void Enemy::CalculateBodyAnchorPoint()
{
	//����� �ڽ��� �ǰ�����Ʈ
	m_BodyAnchorPointForDebugBox = Vec2(0.f, 0.f);

	//���� �浹�� �ǰ�����Ʈ
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
	else if (tag == RED_BOX_SOLID_TAG)
	{
		box->drawSolidRect(vertex[0], vertex[1], Color4F(1.0f, 0.0f, 0.0f, 1.0f));
	}
	else if (tag == GREEN_BOX_SOLID_TAG)
	{
		box->drawSolidRect(vertex[0], vertex[1], Color4F(0.0f, 1.0f, 0.0f, 1.0f));
	}
	else
	{
		return;
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

	setAttackChecked(false);
	m_pAnimationMaker->SetAnimationAttack();
	auto Sprite = m_pAnimationMaker->AddAnimation(getDirection());

	if (getEnemyType() != ENEMY_TYPE::ANCIENT_TREE)
	{
		char buf[255];
		auto i = EnemyManager::getInstance()->getSoundPlayNum();
		sprintf(buf, "%s%d%s", getAttackSound(), i, getAttackSoundExtension());
		i = (i + 1) % 5;
		EnemyManager::getInstance()->setSoundPlayNum(i);

		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(buf, false);
	}
	else
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(getAttackSound(), false);
	}

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

// ENEMY���� State�� ���� ���� � ENEMY�� � �ൿ�� ���ؾ� ���� �����ϴ� �Լ�.
void Enemy::DecideWhatIsCurrentAnimation()
{
	auto currentStateType = getState()->returnStateNumber();
	if (currentStateType == ENEMY_STATE_TYPE::APPROACHING
		|| currentStateType == ENEMY_STATE_TYPE::RETURN
		|| currentStateType == ENEMY_STATE_TYPE::BOSS_RUSH)
	{
		Move();
	}
	else if (currentStateType == ENEMY_STATE_TYPE::ATTACKING
		|| currentStateType == ENEMY_STATE_TYPE::BOSS_ATTACK
		|| currentStateType == ENEMY_STATE_TYPE::BOSS_STRIKE
		|| currentStateType == ENEMY_STATE_TYPE::BOSS_SUMMON)
	{
		Attack();
	}
	else if (currentStateType == ENEMY_STATE_TYPE::SEARCHING
		|| currentStateType == ENEMY_STATE_TYPE::WAITING
		|| currentStateType == ENEMY_STATE_TYPE::BE_ATTACKED)
	{
		Stop();
	}

	// TODO :: BOSS State �Ǻ��� �ֱ�.

	return;
}


// Enemy�� ���� MaxHP���� Ȯ���ϴ� �Լ�.
// ���� HP�� MaxHP�� ���ٸ� true��, �ƴ϶�� false ��ȯ.
bool Enemy::IsEnemyMaxHp()
{
	if (getHP() == getMaxHP())
	{
		return true;
	}

	return false;
}

// Enemy�� Attack�޾Ҵ��� �ʾҴ��� Ȯ���ϴ� �Լ�.
void Enemy::CheckEnemyAttacked()
{
	if (!IsEnemyMaxHp())
	{
		setIsAttackedOnce(true);
	}

	return;
}

// Enemy�� Attack�޾��� ��� Damage�� �޴� �Լ�.
bool Enemy::setAttackedDamage(int damage)
{

	//�ϴ� ¥���� ���� damage
	auto randomDamage = rand() % 2;

	damage += randomDamage;
	setHP(getHP() - damage);
	CheckEnemyAttacked();

	//attack �޾��� �� �� damage�� �´� effect
	CreateEffect(damage);

	if (getFlagBeAttacked() == false)
	{
		changeState<EnemyState_BeAttacked>();
		setFlagBeAttacked(true);
	}


	return true;
}

ManageEnemyMove * Enemy::getManageEnemyMove()
{
	return m_pManageEnemyMove;
}


void Enemy::CreateEffect(int damage)
{
	m_pEffectManager->MakeEffect(damage);
}


int Enemy::MakeHPBox()
{
	if (getChildByTag(GREEN_BOX_SOLID_TAG) != nullptr)
	{
		removeChildByTag(GREEN_BOX_SOLID_TAG);
	}

	auto anchorPoint = getAnchorPoint();

	auto HPBarStart = Vec2(-m_BodyRangeForCollide.x / 2, m_BodyRangeForCollide.y / 2);

	auto HPBarEnd = Vec2(HPBarStart.x + m_BodyRangeForCollide.x, HPBarStart.y + 10.f);

	auto hpRatio = ((float)m_HP / (float)m_MaxHP);

	auto range = Vec2(HPBarStart.x + m_BodyRangeForCollide.x*hpRatio, HPBarStart.y + 10.f);

	//TODO :ü�¹ٸ� �ؿ��� �ణ����߷��� ��ġ�ϱ�
	char buf[255];
	sprintf(buf, "HP: %d", getHP());
	m_pLabel->setPosition(HPBarStart + Vec2(0, 20));
	m_pLabel->setScale(3.f);
	m_pLabel->setString(buf);

	auto box = DrawNode::create();

	if (getChildByTag(RED_BOX_SOLID_TAG) == nullptr)
	{
		box->drawSolidRect(HPBarStart, HPBarEnd, Color4F(1.0f, 0.0f, 0.0f, 1.0f));
	}

	box->drawSolidRect(HPBarStart, range, Color4F(0.0f, 1.0f, 0.0f, 1.0f));
	addChild(box, 0, GREEN_BOX_SOLID_TAG);

	//CCLOG(buf);
	//if (range.x >= m_BodyRangeForCollide.x / 2)
	//{
	//	MakeBox(HPBarStart, range, GREEN_BOX_SOLID_TAG);
	//}
	//else
	//{
	//	MakeBox(HPBarStart, range, RED_BOX_SOLID_TAG);
	//}
	return 0;
}
