#include "pch.h"
#include "Character.h"
#include "MakeAnimation.h"
#include "TemporaryDefine.h"
#include <bitset>

Character::Character()
{
}

Character::~Character()
{
	delete m_pMakeAnimation;
}

Character * Character::create(const char* const filename, const char* const extention)
{
	auto pSprite = new Character();
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(TEMP_DEFINE::PLIST_FILE_NAME);
	char buffer[256];
	sprintf(buffer, "%sstop%d%s", filename, 2, extention);
	if (!(pSprite->initWithSpriteFrameName(buffer)))
	{
		CC_SAFE_DELETE(pSprite);
		return nullptr;
	}

	pSprite->autorelease();

	pSprite->initOptions(filename, extention);

	return pSprite;
}

void Character::initOptions(const char const* filename, const char const* extention)
{
	this->scheduleUpdate();
	m_pMakeAnimation = MakeAnimation::create(TEMP_DEFINE::ARCH_BISHOP_FILE_NAME, TEMP_DEFINE::SPRITE_FRAME_FILE_EXTENTION);
	addChild(m_pMakeAnimation);
	//����,�̵�,���� ���¸� ��Ÿ���� ���� �ʱ�ȭ
	m_State = 0;
	//�ִϸ��̼������� �ƴ����� ��Ÿ���� ����
	m_ActionAnimationOn = false;
	m_MoveAnimationOn = false;
	m_StopAnimationOn = true;
	//�Է��÷��׸� ó���ϱ� ���� ���� �ʱ�ȭ
	m_Input = 0;
	m_ActionInput = 0;
	m_MoveInput = 0;
	m_CurDirection = TEMP_DEFINE::ACTIONS::NO_MOVE;
	m_BeforeDirection = TEMP_DEFINE::ACTIONS::NO_MOVE;
	m_UnitVector[0] = 0;
	m_UnitVector[1] = 0;
	m_AttackRange.x = TEMP_DEFINE::ARCH_BISHOP_ATTACK_RANGE_X;
	m_AttackRange.y = TEMP_DEFINE::ARCH_BISHOP_ATTACK_RANGE_Y;
	//ü�� �ʱ�ȭ
	m_CurHP = TEMP_DEFINE::MAX_HP;
}

//Ű���� �Էº�Ʈ �÷��׸� �׼Ǻκа�,�����Ӻκ����� ������ ������ ������ �ش�. �����ÿ� ����� ���� ���⿡ ���� ó���� ������.
void Character::SetInput(int inputFromScene)
{
	//��ǲ�� �޾ƿͼ� �׼ǰ� ���������� �����Ѵ�.
	m_Input = inputFromScene;
	m_ActionInput = m_Input & TEMP_DEFINE::ACTIONS::GET_ACTION_BIT;
	m_MoveInput = m_Input & TEMP_DEFINE::ACTIONS::GET_DIRECTION_BIT;

	if (IsErrorInput(m_MoveInput))
	{
		m_MoveInput = TEMP_DEFINE::ACTIONS::NO_MOVE;
		m_CurDirection = m_BeforeDirection;

		m_UnitVector[0] = 0;
		m_UnitVector[1] = 0;

		return;
	}

	m_BeforeDirection = m_CurDirection;
	m_CurDirection = m_MoveInput;

	if (IsTopOn(m_MoveInput))
	{
		m_UnitVector[1] = 1;
	}
	else if (IsBottomOn(m_MoveInput))
	{
		m_UnitVector[1] = -1;
	}
	else
	{
		m_UnitVector[1] = 0;
	}

	if (IsLeftOn(m_MoveInput))
	{
		m_UnitVector[0] = -1;
	}
	else if (IsRightOn(m_MoveInput))
	{
		m_UnitVector[0] = 1;
	}
	else
	{
		m_UnitVector[0] = 0;
	}
}

//�Է¿� ���� ������ ���¸� �ľ��Ѵ�.
void Character::CheckCharacterState()
{
	if (m_ActionAnimationOn == false)
	{
		if (m_ActionInput == TEMP_DEFINE::ACTIONS::ATTACK)
		{
			m_State = TEMP_DEFINE::CHARACTER_STATE::STATE_ATTACK;
		}
		else
		{
			if (m_MoveInput == TEMP_DEFINE::ACTIONS::NO_MOVE)
			{
				m_State = TEMP_DEFINE::CHARACTER_STATE::STATE_STOP;
			}
			else
			{
				m_State = TEMP_DEFINE::CHARACTER_STATE::STATE_MOVE;
			}
		}
	}
	else
	{
		return;
	}
}

//���ݸ���� ��������Ʈ�� ��ӹ��� ��Ŭ������ �־��ش�.
void Character::Attack(float dt)
{
	if (m_ActionAnimationOn == true)
	{
		return;
	}

	stopAllActions();
	auto animate = m_pMakeAnimation->AnimationAttack(m_CurDirection);
	auto attackOn = CallFunc::create(CC_CALLBACK_0(Character::AttackOn, this));
	auto attackOff = CallFunc::create(CC_CALLBACK_0(Character::AttackOff, this));
	auto sequence = Sequence::create(attackOn, animate, attackOff, NULL);
	runAction(sequence);
}

//�̵������ ��������Ʈ�� ��ӹ��� ��Ŭ������ �־��ش�.
void Character::Move(float dt)
{
	if (m_MoveAnimationOn == true && m_BeforeDirection == m_CurDirection && m_BeforeState == m_State)
	{
		return;
	}

	stopAllActions();
	auto animate = m_pMakeAnimation->AnimationMove(m_CurDirection);
	auto moveOn = CallFunc::create(CC_CALLBACK_0(Character::MoveOn, this));
	auto moveOff = CallFunc::create(CC_CALLBACK_0(Character::MoveOff, this));
	auto sequence = Sequence::create(moveOn, animate, moveOff, NULL);
	cocos2d::log("�ȱ����");
	runAction(sequence);
}

//��������� ��������Ʈ�� ��ӹ��� ��Ŭ������ �־��ش�.
void Character::Stop(float dt)
{
	stopAllActions();
	auto animate = m_pMakeAnimation->AnimationStop(m_CurDirection);
	auto stopOn = CallFunc::create(CC_CALLBACK_0(Character::StopOn, this));
	auto stopOff = CallFunc::create(CC_CALLBACK_0(Character::StopOff, this));
	auto sequence = Sequence::create(stopOn, animate, stopOff, NULL);
	runAction(sequence);
}

//�������Ӹ��� �̽�������Ʈ�� ������ �͵��� �����Ѵ�. ���� �ľ�->���
void Character::update(float dt)
{
	//���� �ľ�
	CheckCharacterState();
	//���
	if (m_State == TEMP_DEFINE::CHARACTER_STATE::STATE_ATTACK)
	{
		Attack(dt);
		m_BeforeState = m_State;
	}
	else if (m_State == TEMP_DEFINE::CHARACTER_STATE::STATE_MOVE)
	{
		Move(dt);
		auto currentposition = getPosition();

		auto deltaX = (m_UnitVector[0] * (TEMP_DEFINE::VELOCITY)*dt);
		auto deltaY = (m_UnitVector[1] * (TEMP_DEFINE::VELOCITY)*dt);

		setPositionX(currentposition.x + deltaX);
		setPositionY(currentposition.y + deltaY);
		m_BeforeState = m_State;
	}
	else if (m_State == TEMP_DEFINE::CHARACTER_STATE::STATE_STOP)
	{
		Stop(dt);
		m_BeforeState = m_State;
	}
	MakeHpBar();
}

//��������Ʈ ĳ���� �̹����� �ø���.
void Character::AddSpriteFramesWithFile(const char * filename)
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(filename);
}
void Character::AttackOff()
{
	m_ActionAnimationOn = false;
	m_State = TEMP_DEFINE::CHARACTER_STATE::STATE_STOP;
}
void Character::MoveOff()
{
	m_MoveAnimationOn = false;
	m_State = TEMP_DEFINE::CHARACTER_STATE::STATE_STOP;
}
void Character::StopOff()
{
	m_StopAnimationOn = false;
}

void Character::AttackOn()
{
	m_ActionAnimationOn = true;
}

void Character::MoveOn()
{
	m_MoveAnimationOn = true;
}

void Character::StopOn()
{
	m_StopAnimationOn = true;
}

Vec2 Character::GetCurrentDitection()
{
	auto currentDirection = Vec2(0.0f, 0.0f);
	if (m_CurDirection == TEMP_DEFINE::ACTIONS::BOTTOM)
	{
		currentDirection = Vec2(0.0f, -1.0f);
	}
	else if (m_CurDirection == TEMP_DEFINE::ACTIONS::BOTTOM_LEFT)
	{
		currentDirection = Vec2(-1.0f, -1.0f);
	}
	else if (m_CurDirection == TEMP_DEFINE::ACTIONS::BOTTOM_RIGHT)
	{
		currentDirection = Vec2(1.0f, -1.0f);
	}
	else if (m_CurDirection == TEMP_DEFINE::ACTIONS::LEFT)
	{
		currentDirection = Vec2(-1.0f, 0.0f);
	}
	else if (m_CurDirection == TEMP_DEFINE::ACTIONS::RIGHT)
	{
		currentDirection = Vec2(1.0f, 0.0f);
	}
	else if (m_CurDirection == TEMP_DEFINE::ACTIONS::TOP)
	{
		currentDirection = Vec2(0.0f, 1.0f);
	}
	else if (m_CurDirection == TEMP_DEFINE::ACTIONS::TOP_LEFT)
	{
		currentDirection = Vec2(-1.0f, 1.0f);
	}
	else if (m_CurDirection == TEMP_DEFINE::ACTIONS::TOP_RIGTH)
	{
		currentDirection = Vec2(1.0f, 1.0f);
	}
	return currentDirection;
}

Vec2 Character::GetAttackRange()
{
	return m_AttackRange;
}

int Character::GetCharacterState()
{
	return m_State;
}

int Character::GetCharacterHP()
{
	return m_CurHP;
}

void Character::SetHP(int dHp)
{
	m_CurHP -= dHp;
}

void Character::MakeHpBar()
{
	auto anchorPoint = getAnchorPoint();
	auto hpBarBottomLeftVertex = Vec2(anchorPoint.x + getContentSize().width / 2 - TEMP_DEFINE::MAX_HP * 10 / 2, anchorPoint.y - 5);
	auto hpBarTopRightVertex = Vec2(hpBarBottomLeftVertex.x + (m_CurHP * 10), anchorPoint.y);
	if (getChildByTag(1) != nullptr)
	{
		removeChildByTag(1);
	}
	auto box = DrawNode::create();
	box->drawRect(hpBarBottomLeftVertex, hpBarTopRightVertex, Color4F(1.0f, 0.0f, 0.0f, 1.0f));
	addChild(box, 0, 1);
}

bool Character::IsTopOn(int m_MoveInput)
{
	return m_MoveInput & TEMP_DEFINE::ACTIONS::TOP;
}

bool Character::IsBottomOn(int m_MoveInput)
{
	return m_MoveInput & TEMP_DEFINE::ACTIONS::BOTTOM;
}

bool Character::IsLeftOn(int m_MoveInput)
{
	return m_MoveInput & TEMP_DEFINE::ACTIONS::LEFT;
}

bool Character::IsRightOn(int m_MoveInput)
{
	return m_MoveInput & TEMP_DEFINE::ACTIONS::RIGHT;
}

bool Character::IsErrorInput(int m_MoveInput)
{
	bool isError = false;
	if (m_MoveInput == 0)
	{
		isError = true;
	}
	else if (m_MoveInput == 3)
	{
		isError = true;
	}
	else if (m_MoveInput == 7)
	{
		isError = true;
	}
	else if (m_MoveInput >= 11 && m_MoveInput <= 15)
	{
		isError = true;
	}

	return isError;
}