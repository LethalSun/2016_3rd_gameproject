#include "pch.h"
#include "PlayerCharacter.h"
#include "AnimationMaker.h"

PlayerCharacter * PlayerCharacter::create(const char * fileName, const char * fileExtention)
{
	auto pPlayerCharacter = new(std::nothrow) PlayerCharacter();
	if (pPlayerCharacter&&pPlayerCharacter->init(fileName, fileExtention))
	{
		pPlayerCharacter->autorelease();
		return pPlayerCharacter;
	}
	else
	{
		delete pPlayerCharacter;
		pPlayerCharacter = nullptr;
		return pPlayerCharacter;
	}
}

bool PlayerCharacter::init(const char * fileName, const char * fileExtention)
{
	if (!(Node::init()))
	{
		return false;
	}

	//ü���� �ʱ�ȭ
	m_MaxHP = MAX_HP;
	m_HP = MAX_HP;

	//������ �ʱ�ȭ
	m_MaxSP = MAX_SP;
	m_SP = MAX_SP;

	//��ų�� �ʱ�ȭ
	m_DefenseSkill = nullptr;
	m_AttackSkill = nullptr;

	//���¸� ������ �ʱ�ȭ
	m_State = STATE::STOP;

	//������ �Ʒ��� �ʱ�ȭ
	m_Direction = DIRECTION::BOTTOM;

	//�ִϸ��̼��� �ʱ�ȭ
	m_pAnimationMaker = AnimationMaker::create(fileName, fileExtention);
	m_pAnimationMaker->SetAnimationStop();
	m_pAnimationMaker->AddAnimation(m_Direction);
}

int PlayerCharacter::GetState()
{
	return m_State;
}

void PlayerCharacter::SetState(int state)
{
	m_BeforeState = m_State;
	m_State = state;
}

int PlayerCharacter::GetDirection()
{
	return m_Direction;
}

void PlayerCharacter::SetDirection(int direction)
{
	m_BeforeDirection = m_Direction;
	m_Direction = direction;
}

void PlayerCharacter::AddAnimation(int direction)
{
	m_pAnimationMaker->AddAnimation(direction);
}

int PlayerCharacter::GetHP()
{
	return m_HP;
}

void PlayerCharacter::SetHP(int hp)
{
	m_HP = hp;
}

int PlayerCharacter::GetSP()
{
	return m_SP;
}

void PlayerCharacter::SetSP(int sp)
{
	m_SP = sp;
}

PlayerCharacter::PlayerCharacter()
{
}

PlayerCharacter::~PlayerCharacter()
{
}