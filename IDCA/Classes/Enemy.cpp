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
#include "Tentacle.h"

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
	m_pEnemyManager = EnemyManager::getInstance();

	addChild(m_pEffectManager, 5);
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

// float 형태의 유닛벡터를 받아서 int형태의 값으로 바꿔준다.
// IgnoreMoveRange의 범위 만큼은 무시하여 흔들림을 보정해준다.
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

// Before State와 Direction을 저장해주는 함수.
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

	EnemyAttackSound();


	CalculateAttackAnchorPoint();
	//MakeBox(m_AttackAnchorPointForDebugBox, m_AttackRangeForCollide, m_RedBoxTag);

	return true;
}

// Enemy의 공격하는 소리를 재생해주는 함수.
void Enemy::EnemyAttackSound()
{
	// 보스가 아닌 경우 공격 소리 처리.
	if (getEnemyType() != ENEMY_TYPE::ANCIENT_TREE) 
	{
		// 여러 Enemy가 같이 공격할 경우 소리가 나지 않아서 임시방편으로 대체.
		char buf[255];
		auto i = EnemyManager::getInstance()->getSoundPlayNum();
		sprintf(buf, "%s%d%s", getAttackSound(), i, getAttackSoundExtension());
		i = (i + 1) % 5;

		EnemyManager::getInstance()->setSoundPlayNum(i);

		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(buf, false);
	}
	// 보스일 경우 그냥 공격 음향 재생.
	else
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(getAttackSound(), false);
	}

	return;
}

// State Attack이 계속되고 있는지 확인해 주는 함수.
bool Enemy::IsAttackContinued()
{
	// 현재 STATE가 Attack인지, 직전 방향과 현재 방향이 맞는지, 직전 STATE와 현재 STATE가 맞는지 확인.
	if (m_pAnimationMaker->IsAnimationContinued() == STATE::ATTACK
		&& (getBeforeDirection() == getDirection())
		&& (getBeforeState() == getState()))
	{
		return true;
	}

	// 하나라도 다르다면 STATE가 계속 되고 있지 않는다고 판단.
	return false;
}

// ENEMY들의 State에 따라서 지금 어떤 ENEMY가 어떤 행동을 취해야 할지 결정하는 함수.
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
		|| currentStateType == ENEMY_STATE_TYPE::BOSS_SUMMON)
	{
		Attack();
	}
	else if (currentStateType == ENEMY_STATE_TYPE::SEARCHING
		|| currentStateType == ENEMY_STATE_TYPE::WAITING
		|| currentStateType == ENEMY_STATE_TYPE::BE_ATTACKED
		|| currentStateType == ENEMY_STATE_TYPE::BOSS_STRIKE)
	{
		Stop();
	}

	return;
}


// Enemy가 현재 MaxHP인지 확인하는 함수.
// 현재 HP와 MaxHP가 같다면 true를, 아니라면 false 반환.
bool Enemy::IsEnemyMaxHp()
{
	if (getHP() == getMaxHP())
	{
		return true;
	}

	return false;
}

// Enemy가 Attack받았는지 않았는지 확인하는 함수.
void Enemy::CheckEnemyAttacked()
{
	if (!IsEnemyMaxHp())
	{
		setIsAttackedOnce(true);
	}

	return;
}

// Enemy가 Attack받았을 경우 Damage를 받는 함수.
bool Enemy::setAttackedDamage(int damage)
{

	//일단 짜잘한 랜덤 damage
	auto randomDamage = rand() % 2;

	damage += randomDamage;
	setHP(getHP() - damage);
	CheckEnemyAttacked();

	//attack 받았을 때 그 damage로 맞는 effect
	CreateEffect(damage);

	setFlagBeAttacked(true);
	changeState<EnemyState_BeAttacked>();

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

	//TODO :체력바를 밑에서 약간떯어뜨려서 배치하기
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


// 현재 Player의 Position에 Boss 공격용 텐타클을 만들어주는 함수.
void Enemy::MakeTentacle()
{
	// TODO :: 매직넘버 없애고 보스 체력에 반비례하여 빠르게 만들어지게.
	auto tentacle = Tentacle::create(getPlayerPosition(), 3.0f, 20.f, getMapPointer(), true);
	getMapPointer()->addChild(tentacle);
	return;
}

// Boss의 Strike 구현.
void Enemy::Strike()
{
	// 8방향에 대해서 텐타클 만들어주기.
	const float distance = 45.f;
	auto bossPosition = getPosition();
	for (int i = 0; i < 4; ++i)
	{
		auto createPosition = Vec2(bossPosition.x, bossPosition.y + distance * (i + 1));
		auto duration = 0.5f * (i + 1);
		auto tentacle = Tentacle::create(createPosition, duration, 20.f, getMapPointer(), false);
		getMapPointer()->addChild(tentacle);
	}
	for (int i = 0; i < 4; ++i)
	{
		auto createPosition = Vec2(bossPosition.x + distance * (i + 1), bossPosition.y + distance * (i + 1));
		auto duration = 0.5f * (i + 1);
		auto tentacle = Tentacle::create(createPosition, duration, 20.f, getMapPointer(), false);
		getMapPointer()->addChild(tentacle);
	}
	for (int i = 0; i < 4; ++i)
	{
		auto createPosition = Vec2(bossPosition.x + distance * (i + 1), bossPosition.y);
		auto duration = 0.5f * (i + 1);
		auto tentacle = Tentacle::create(createPosition, duration, 20.f, getMapPointer(), false);
		getMapPointer()->addChild(tentacle);
	}
	for (int i = 0; i < 4; ++i)
	{
		auto createPosition = Vec2(bossPosition.x + distance * (i + 1), bossPosition.y - distance * (i + 1));
		auto duration = 0.5f * (i + 1);
		auto tentacle = Tentacle::create(createPosition, duration, 20.f, getMapPointer(), false);
		getMapPointer()->addChild(tentacle);
	}
	for (int i = 0; i < 4; ++i)
	{
		auto createPosition = Vec2(bossPosition.x, bossPosition.y - distance * (i + 1));
		auto duration = 0.5f * (i + 1);
		auto tentacle = Tentacle::create(createPosition, duration, 20.f, getMapPointer(), false);
		getMapPointer()->addChild(tentacle);
	}
	for (int i = 0; i < 4; ++i)
	{
		auto createPosition = Vec2(bossPosition.x - distance * (i + 1), bossPosition.y - distance * (i + 1));
		auto duration = 0.5f * (i + 1);
		auto tentacle = Tentacle::create(createPosition, duration, 20.f, getMapPointer(), false);
		getMapPointer()->addChild(tentacle);
	}
	for (int i = 0; i < 4; ++i)
	{
		auto createPosition = Vec2(bossPosition.x - distance * (i + 1), bossPosition.y);
		auto duration = 0.5f * (i + 1);
		auto tentacle = Tentacle::create(createPosition, duration, 20.f, getMapPointer(), false);
		getMapPointer()->addChild(tentacle);
	}
	for (int i = 0; i < 4; ++i)
	{
		auto createPosition = Vec2(bossPosition.x - distance * (i + 1), bossPosition.y + distance * (i + 1));
		auto duration = 0.5f * (i + 1);
		auto tentacle = Tentacle::create(createPosition, duration, 20.f, getMapPointer(), false);
		getMapPointer()->addChild(tentacle);
	}
	return;
}
