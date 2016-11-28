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

	//체력을 초기화
	m_MaxHP = MAX_HP;
	m_HP = MAX_HP;

	//마나를 초기화
	m_MaxSP = MAX_SP;
	m_SP = MAX_SP;

	//스킬을 초기화
	m_DefenseSkill = nullptr;
	m_AttackSkill = nullptr;

	//상태를 정지로 초기화
	m_State = STATE::STOP;

	//방향을 아래로 초기화
	m_Direction = DIRECTION::BOTTOM;

	//애니메이션을 초기화
	m_pAnimationMaker = AnimationMaker::create(fileName, fileExtention);
	m_pAnimationMaker->SetAnimationStop();
	m_pAnimationMaker->AddAnimation(m_Direction);

	addChild(m_pAnimationMaker);
}

int PlayerCharacter::GetState()
{
	return m_State;
}

void PlayerCharacter::SetState(int state)
{
	m_State = state;
}

int PlayerCharacter::GetDirection()
{
	return m_Direction;
}

void PlayerCharacter::SetDirection(int direction)
{
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

void PlayerCharacter::update(float dt)
{
	if (m_State == STATE::ATTACK)
	{
		Attack();
	}
	else if (m_State == STATE::MOVE)
	{
		Move();
	}
	else if (m_State == STATE::STOP)
	{
		stop();
	}
	else if (m_State == STATE::SKILL)
	{
		skill();
	}
	CheckStopState();
	SaveBeforeStateAndDirection();
}

void PlayerCharacter::Attack()
{
	if (IsAttackContinued())
	{
		return;
	}

	m_pAnimationMaker->SetAnimationAttack();
	m_pAnimationMaker->AddAnimation(m_Direction);
}

void PlayerCharacter::Move()
{
	if (IsMoveContinued())
	{
		return;
	}

	m_pAnimationMaker->stopAllActions();
	m_pAnimationMaker->SetAnimationMove();
	m_pAnimationMaker->AddAnimation(m_Direction);
}

void PlayerCharacter::stop()
{
	m_pAnimationMaker->stopAllActions();
	m_pAnimationMaker->SetAnimationStop();
	m_pAnimationMaker->AddAnimation(m_Direction);
}

void PlayerCharacter::skill()
{
	return;
}

void PlayerCharacter::CheckStopState()
{
	if (m_pAnimationMaker->IsAnimationContinued == -1)
	{
		if (m_State == STATE::ATTACK)
		{
			m_State = STATE::STOP;
		}
		else if (m_State == STATE::MOVE)
		{
			m_State = STATE::STOP;
		}
	}
}

bool PlayerCharacter::init()
{
	return false;
}

PlayerCharacter::PlayerCharacter()
{
}

PlayerCharacter::~PlayerCharacter()
{
}

bool PlayerCharacter::IsAttackContinued()
{
	if (m_pAnimationMaker->IsAnimationContinued == STATE::MOVE
		&& m_BeforeDirection == m_Direction
		&& m_BeforeState == m_State)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool PlayerCharacter::IsMoveContinued()
{
	if (m_pAnimationMaker->IsAnimationContinued == STATE::ATTACK)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void PlayerCharacter::SaveBeforeStateAndDirection()
{
	m_BeforeState = m_State;
	m_BeforeDirection = m_Direction;
}