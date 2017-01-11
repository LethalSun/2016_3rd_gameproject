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
#include "BossState_Summon.h"
#include "EffectManager.h"
#include "Tentacle.h"

const Vec2 ZERO = Vec2(0.f, 0.f);

bool Enemy::init(const Vec2 initPosition)
{
	if (!Node::init())
	{
		return false;
	}

	m_pManageEnemyMove = ManageEnemyMove::create();
	m_pEffectManager = EffectManager::create();
	m_pEnemyManager = EnemyManager::getInstance();

	addChild(m_pEffectManager, ENEMY_EFFECT_MANAGER_ZORDER);
	addComponent(m_pManageEnemyMove);

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
	
	setBeforePosition(Vec2(-1, -1));


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
	CheckBossStatus();

	MakeMaxHPBox();
	MakeHPBox();
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

	auto beforePosition = getPosition();
	auto position = m_pManageEnemyMove->update(this->getPosition(), getTranslatedUnitVec(), getMapPointer(), deltaTime, this);

	//줄서서 기다리지 않아보자.
	auto unitVec = getTranslatedUnitVec();

	while (beforePosition == position)
	{
		if (unitVec.x == 0)
		{
			auto randomValue = rand() % 2;
			if (randomValue == 0)
			{
				unitVec.x += 1;
			}
			else
			{
				unitVec.x += -1;
			}
		}
		else if (unitVec.y == 0)
		{
			auto randomValue = rand() % 2;
			if (randomValue == 0)
			{
				unitVec.y += 1;
			}
			else
			{
				unitVec.y += -1;
			}
		}
		else
		{
			auto randomValue = rand() % 2;
			if (randomValue == 0)
			{
				unitVec.x = 0;
			}
			else
			{
				unitVec.y = 0;
			}

		}
		position = m_pManageEnemyMove->update(getPosition(), unitVec, getMapPointer(), deltaTime, this);
	}


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

	if (abs(InputUnitVec.x) > ENEMY_IGNORE_MOVE_RANGE)
	{
		x = (InputUnitVec.x > 0) ? 1 : -1;
	}
	else
	{
		x = 0;
	}

	if (abs(InputUnitVec.y) > ENEMY_IGNORE_MOVE_RANGE)
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
	if (m_pAnimationMaker->whichAnimationContinued() == STATE::STOP
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
	if (m_pAnimationMaker->whichAnimationContinued() == STATE::MOVE
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
		i = (i + 1) % ENEMY_ATTACK_SOUND_NUMBER;

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
	if (m_pAnimationMaker->whichAnimationContinued() == STATE::ATTACK
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
	auto currentHP = getHP() - damage;
	if (currentHP < 0)
	{
		setHP(0);
	}
	else
	{
		setHP(currentHP);
	}
	CheckEnemyAttacked();

	//attack 받았을 때 그 damage로 맞는 effect
	CreateEffect(damage);

	setFlagBeAttacked(true);

	// 보스일 경우, BeAttacked상태에 들어가지 않고 공격을 계속 하게 된다.
	if (getEnemyType() != ENEMY_TYPE::ANCIENT_TREE)
	{
		changeState<EnemyState_BeAttacked>();
	}
	else
	{
		// TintBy를 사용하여 빨갛게 되는 액션과 다시 돌아오는 Action을 만든다.
		m_pAnimationMaker->GetSprite()->stopActionByTag(TINT_ACTION_TAG);
		TintBy* redAction = TintBy::create(ENEMY_RED_ACTION_TIME, 0, -255, -255);
		TintBy* recoveryAction = TintBy::create(ENEMY_RED_ACTION_TIME, 0, 255, 255);

		auto seqAction = Sequence::create(redAction, recoveryAction, nullptr);
		seqAction->setTag(TINT_ACTION_TAG);
		m_pAnimationMaker->GetSprite()->runAction(seqAction);
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(getHitedSound(), false);
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

	auto hpCurrent = Sprite::create("Board/hp.png");
	auto positionOfSprite = positiionOfHp;
	hpCurrent->setPosition(Vec2(-positionOfSprite.x / 2, -positionOfSprite.y / 2));
	hpCurrent->setAnchorPoint(Vec2(0, 0));

	auto hpRatio = ((float)getHP() / (float)getMaxHP());

	hpCurrent->setScaleY(sizeOfHp_y);
	hpCurrent->setScaleX(hpRatio*sizeOfHp_x);

	addChild(hpCurrent, 0, GREEN_BOX_SOLID_TAG);

	return 0;
}

int Enemy::MakeMaxHPBox()
{
	if (getChildByTag(RED_BOX_SOLID_TAG) == nullptr)
	{
		auto hpMax = Sprite::create("Board/hpMax.png");
		auto positionOfSprite = positiionOfHp;
		hpMax->setPosition(Vec2(-positionOfSprite.x / 2, -positionOfSprite.y / 2));

		hpMax->setAnchorPoint(Vec2(0, 0));
		hpMax->setScaleY(sizeOfHp_y);
		hpMax->setScaleX(sizeOfHp_x);
		addChild(hpMax, 1, RED_BOX_SOLID_TAG);
	}
	else{}

	return 0;

}

// 현재 Player의 Position에 Boss 공격용 텐타클을 만들어주는 함수.
void Enemy::MakeTentacle()
{
	auto tentacle = Tentacle::create(getPlayerPosition(), getAttackFrequency() * 2, getDamage(), getMapPointer(), getInnerCollideManager(), true);
	getMapPointer()->addChild(tentacle);
	return;
}

// Boss의 Strike 구현.
void Enemy::Strike()
{
	// 8방향에 대해서 텐타클 만들어주기.

	auto bossPosition = getPosition();
	for (int i = 0; i < STRIKE_TENTACLE_NUMBER; ++i)
	{
		auto createPosition = Vec2(bossPosition.x, bossPosition.y + STRIKE_DISTANCE * (i + 1));
		auto duration = getAttackFrequency() * (i + 1) * STRIKE_CORRECTION_FLOAT;
		auto tentacle = Tentacle::create(createPosition, duration, getDamage(), getMapPointer(), getInnerCollideManager(), false);
		getMapPointer()->addChild(tentacle);
	}
	for (int i = 0; i < STRIKE_TENTACLE_NUMBER; ++i)
	{
		auto createPosition = Vec2(bossPosition.x + STRIKE_DISTANCE * (i + 1), bossPosition.y + STRIKE_DISTANCE * (i + 1));
		auto duration = getAttackFrequency() * (i + 1) * STRIKE_CORRECTION_FLOAT;
		auto tentacle = Tentacle::create(createPosition, duration, getDamage(), getMapPointer(), getInnerCollideManager(), false);
		getMapPointer()->addChild(tentacle);
	}
	for (int i = 0; i < STRIKE_TENTACLE_NUMBER; ++i)
	{
		auto createPosition = Vec2(bossPosition.x + STRIKE_DISTANCE * (i + 1), bossPosition.y);
		auto duration = getAttackFrequency() * (i + 1) * STRIKE_CORRECTION_FLOAT;
		auto tentacle = Tentacle::create(createPosition, duration, getDamage(), getMapPointer(), getInnerCollideManager(), false);
		getMapPointer()->addChild(tentacle);
	}
	for (int i = 0; i < STRIKE_TENTACLE_NUMBER; ++i)
	{
		auto createPosition = Vec2(bossPosition.x + STRIKE_DISTANCE * (i + 1), bossPosition.y - STRIKE_DISTANCE * (i + 1));
		auto duration = getAttackFrequency() * (i + 1) * STRIKE_CORRECTION_FLOAT;
		auto tentacle = Tentacle::create(createPosition, duration, getDamage(), getMapPointer(), getInnerCollideManager(), false);
		getMapPointer()->addChild(tentacle);
	}
	for (int i = 0; i < STRIKE_TENTACLE_NUMBER; ++i)
	{
		auto createPosition = Vec2(bossPosition.x, bossPosition.y - STRIKE_DISTANCE * (i + 1));
		auto duration = getAttackFrequency() * (i + 1) * STRIKE_CORRECTION_FLOAT;
		auto tentacle = Tentacle::create(createPosition, duration, getDamage(), getMapPointer(), getInnerCollideManager(), false);
		getMapPointer()->addChild(tentacle);
	}
	for (int i = 0; i < STRIKE_TENTACLE_NUMBER; ++i)
	{
		auto createPosition = Vec2(bossPosition.x - STRIKE_DISTANCE * (i + 1), bossPosition.y - STRIKE_DISTANCE * (i + 1));
		auto duration = getAttackFrequency() * (i + 1) * STRIKE_CORRECTION_FLOAT;
		auto tentacle = Tentacle::create(createPosition, duration, getDamage(), getMapPointer(), getInnerCollideManager(), false);
		getMapPointer()->addChild(tentacle);
	}
	for (int i = 0; i < STRIKE_TENTACLE_NUMBER; ++i)
	{
		auto createPosition = Vec2(bossPosition.x - STRIKE_DISTANCE * (i + 1), bossPosition.y);
		auto duration = getAttackFrequency() * (i + 1) * STRIKE_CORRECTION_FLOAT;
		auto tentacle = Tentacle::create(createPosition, duration, getDamage(), getMapPointer(), getInnerCollideManager(), false);
		getMapPointer()->addChild(tentacle);
	}
	for (int i = 0; i < STRIKE_TENTACLE_NUMBER; ++i)
	{
		auto createPosition = Vec2(bossPosition.x - STRIKE_DISTANCE * (i + 1), bossPosition.y + STRIKE_DISTANCE * (i + 1));
		auto duration = getAttackFrequency() * (i + 1) * STRIKE_CORRECTION_FLOAT;
		auto tentacle = Tentacle::create(createPosition, duration, getDamage(), getMapPointer(), getInnerCollideManager(), false);
		getMapPointer()->addChild(tentacle);
	}
	return;
}

// Boss의 체력 나머지와 Raged 여부를 검사하는 함수. Update에서 호출.
void Enemy::CheckBossStatus()
{
	// 보스가 아니라면, return.
	if (getEnemyType() != ENEMY_TYPE::ANCIENT_TREE)
	{
		return;
	}

	// 남은 체력의 비율을 계산한 뒤, 
	auto hpRatio = (float)getHP() / (float)getMaxHP();
	setRemainHpPercent(hpRatio);

	// 남은 체력 비율에 반비례하여 AttackFrequency 결정, 그리고 Summon.
	if (!getIsRaged30() && (getRemainHpPercent() < ANCIENT_TREE_RAGE30))
	{
		setIsRaged30(true);
		setAttackFrequency(ANCIENT_TREE_RAGE30_RATE);
		changeState<BossState_Summon>();
	}
	else if (!getIsRaged60() && (getRemainHpPercent() < ANCIENT_TREE_RAGE60))
	{
		setIsRaged60(true);
		setAttackFrequency(ANCIENT_TREE_RAGE60_RATE);
		changeState<BossState_Summon>();
	}

	return;
}
