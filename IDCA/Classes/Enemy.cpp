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

	auto beforePosition = getPosition();
	auto position = m_pManageEnemyMove->update(this->getPosition(), getTranslatedUnitVec(), getMapPointer(), deltaTime, this);

	//�ټ��� ��ٸ��� �ʾƺ���.
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

// Enemy�� �����ϴ� �Ҹ��� ������ִ� �Լ�.
void Enemy::EnemyAttackSound()
{
	// ������ �ƴ� ��� ���� �Ҹ� ó��.
	if (getEnemyType() != ENEMY_TYPE::ANCIENT_TREE) 
	{
		// ���� Enemy�� ���� ������ ��� �Ҹ��� ���� �ʾƼ� �ӽù������� ��ü.
		char buf[255];
		auto i = EnemyManager::getInstance()->getSoundPlayNum();
		sprintf(buf, "%s%d%s", getAttackSound(), i, getAttackSoundExtension());
		i = (i + 1) % ENEMY_ATTACK_SOUND_NUMBER;

		EnemyManager::getInstance()->setSoundPlayNum(i);

		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(buf, false);
	}
	// ������ ��� �׳� ���� ���� ���.
	else
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(getAttackSound(), false);
	}

	return;
}

// State Attack�� ��ӵǰ� �ִ��� Ȯ���� �ִ� �Լ�.
bool Enemy::IsAttackContinued()
{
	// ���� STATE�� Attack����, ���� ����� ���� ������ �´���, ���� STATE�� ���� STATE�� �´��� Ȯ��.
	if (m_pAnimationMaker->whichAnimationContinued() == STATE::ATTACK
		&& (getBeforeDirection() == getDirection())
		&& (getBeforeState() == getState()))
	{
		return true;
	}

	// �ϳ��� �ٸ��ٸ� STATE�� ��� �ǰ� ���� �ʴ´ٰ� �Ǵ�.
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

	//attack �޾��� �� �� damage�� �´� effect
	CreateEffect(damage);

	setFlagBeAttacked(true);

	// ������ ���, BeAttacked���¿� ���� �ʰ� ������ ��� �ϰ� �ȴ�.
	if (getEnemyType() != ENEMY_TYPE::ANCIENT_TREE)
	{
		changeState<EnemyState_BeAttacked>();
	}
	else
	{
		// TintBy�� ����Ͽ� ������ �Ǵ� �׼ǰ� �ٽ� ���ƿ��� Action�� �����.
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

// ���� Player�� Position�� Boss ���ݿ� ��ŸŬ�� ������ִ� �Լ�.
void Enemy::MakeTentacle()
{
	auto tentacle = Tentacle::create(getPlayerPosition(), getAttackFrequency() * 2, getDamage(), getMapPointer(), getInnerCollideManager(), true);
	getMapPointer()->addChild(tentacle);
	return;
}

// Boss�� Strike ����.
void Enemy::Strike()
{
	// 8���⿡ ���ؼ� ��ŸŬ ������ֱ�.

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

// Boss�� ü�� �������� Raged ���θ� �˻��ϴ� �Լ�. Update���� ȣ��.
void Enemy::CheckBossStatus()
{
	// ������ �ƴ϶��, return.
	if (getEnemyType() != ENEMY_TYPE::ANCIENT_TREE)
	{
		return;
	}

	// ���� ü���� ������ ����� ��, 
	auto hpRatio = (float)getHP() / (float)getMaxHP();
	setRemainHpPercent(hpRatio);

	// ���� ü�� ������ �ݺ���Ͽ� AttackFrequency ����, �׸��� Summon.
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
