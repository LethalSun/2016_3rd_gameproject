#include "pch.h"
#include "PlayerCharacter.h"
#include "AnimationMaker.h"
#include <windows.h>
#include <iostream>

PlayerCharacter::PlayerCharacter(const Vec2 AttackRange, const Vec2 BodyRange)
	:m_RedBoxTag(RED_BOX_TAG),
	m_GreenBoxTag(GREEN_BOX_TAG),
	m_AttackRange(AttackRange),
	m_BodyRange(BodyRange)
{
}

PlayerCharacter::~PlayerCharacter()
{
}

PlayerCharacter * PlayerCharacter::create(const char * fileName, const char * fileExtention)
{
	PlayerCharacter* pPlayerCharacter(nullptr);
	String filename = fileName;
	if (filename.compare("archbishop") == 0)
	{
		auto attackRange = Vec2(ARCHBISHOP_ATTACK_RANGE, ARCHBISHOP_ATTACK_RANGE);
		auto bodyRange = Vec2(ARCHBISHOP_BODY_RANGE_X, ARCHBISHOP_BODY_RANGE_Y);
		pPlayerCharacter = new(std::nothrow) PlayerCharacter(attackRange, bodyRange);
	}
	else if (filename.compare("Worrior") == 0)
	{
		auto attackRange = Vec2(WORRIOR_ATTACK_RANGE, WORRIOR_ATTACK_RANGE);
		auto bodyRange = Vec2(WORRIOR_BODY_RANGE_X, WORRIOR_BODY_RANGE_Y);
		pPlayerCharacter = new(std::nothrow) PlayerCharacter(attackRange, bodyRange);
	}

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

	//데미지 초기화
	m_Damage = ATTACK_DAMAGE;
	//스킬을 초기화
	m_DefenseSkill = nullptr;
	m_AttackSkill = nullptr;

	//상태를 정지로 초기화
	m_State = STATE::STOP;

	//방향을 아래로 초기화
	m_Direction = DIRECTION::BOTTOM;

	//애니메이션을 초기화
	m_pAnimationMaker = AnimationMaker::create(fileName, fileExtention);
	addChild(m_pAnimationMaker);
	m_pAnimationMaker->SetAnimationStop();
	m_pAnimationMaker->AddAnimation(m_Direction);
	//체력 숫자 표시용 레이블
	m_pLabel = Label::create();
	m_pLabel->setColor(ccc3(255, 0, 0));
	addChild(m_pLabel, 5);
	//addChild(Sprite);
}

int PlayerCharacter::GetState()
{
	return m_State;
}

void PlayerCharacter::SetState(int state)
{
	if (IsAttackContinued())
	{
		return;
	}
	m_State = state;
}

int PlayerCharacter::GetDirection()
{
	return m_Direction;
}

void PlayerCharacter::SetDirection(int direction)
{
	if (IsAttackContinued())
	{
		return;
	}
	m_Direction = direction;
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

int PlayerCharacter::GetDamage()
{
	return m_Damage;
}

void PlayerCharacter::SetDamage(int damage)
{
	m_Damage = damage;
}

void PlayerCharacter::update(float dt)
{
	//m_pAnimationMaker->GetSprite()->stopAllActions();
	if (m_State == STATE::ATTACK)
	{
		Attack();
		for (int i = 0; i < 50; ++i)
		{
			MakeBox(m_AttackAnchorPointForDebugBox, m_AttackRange, RED_BOX_TAG);
		}
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
	MakeHPBox();
	SaveBeforeStateAndDirection();
	CheckStopState();
}

void PlayerCharacter::Attack()
{
	if (IsAttackContinued())
	{
		return;
	}
	m_AttackChecked = false;
	m_pAnimationMaker->SetAnimationAttack();
	auto Sprite = m_pAnimationMaker->AddAnimation(m_Direction);
}

void PlayerCharacter::Move()
{
	if (IsMoveContinued())
	{
		return;
	}
	m_pAnimationMaker->SetAnimationMove();
	auto Sprite = m_pAnimationMaker->AddAnimation(m_Direction);
}

void PlayerCharacter::stop()
{
	m_pAnimationMaker->SetAnimationStop();
	auto Sprite = m_pAnimationMaker->AddAnimation(m_Direction);
}

void PlayerCharacter::skill()
{
	return;
}

void PlayerCharacter::CheckStopState()
{
	if (m_pAnimationMaker->IsAnimationContinued() == -1)
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

Vec2 PlayerCharacter::GetAttackAnchorPoint()
{
	return m_AttackAnchorPoint;
}

void PlayerCharacter::SetAttackAnchorPoint(Vec2 attackAnchorPoint)
{
	m_AttackAnchorPoint = attackAnchorPoint;
}

Vec2 PlayerCharacter::GetBodyAnchorPoint()
{
	return m_BodyAnchorPoint;
}

void PlayerCharacter::SetBodyAnchorPoint(Vec2 bodyAnchorPoint)
{
	m_BodyAnchorPoint = bodyAnchorPoint;
}

Vec2 PlayerCharacter::GetAttackRange()
{
	return m_AttackRange;
}

Vec2 PlayerCharacter::GetBodyRange()
{
	return m_BodyRange;
}

void PlayerCharacter::SetAttackAnchorPointForMakeDebugBox(Vec2 attackAnchorPointForDebugBox)
{
	m_AttackAnchorPointForDebugBox = attackAnchorPointForDebugBox;
}

void PlayerCharacter::SetBodyAnchorPointForMakeDebugBox(Vec2 bodyAnchorPointForDebugBox)
{
	m_BodyAnchorPointForDebugBox = bodyAnchorPointForDebugBox;
}

bool PlayerCharacter::IsAttackChecked()
{
	if (m_AttackChecked == true)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void PlayerCharacter::SetAttackChecked()
{
	m_AttackChecked = true;
}

bool PlayerCharacter::IsAttackContinued()
{
	if (m_pAnimationMaker->IsAnimationContinued() == STATE::ATTACK
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
	if (m_pAnimationMaker->IsAnimationContinued() == STATE::MOVE
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

void PlayerCharacter::SaveBeforeStateAndDirection()
{
	m_BeforeState = m_State;
	m_BeforeDirection = m_Direction;
}

void PlayerCharacter::MakeBox(Vec2 position, Vec2 boxInfo, const int tag)
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

int PlayerCharacter::MakeHPBox()
{
	auto HPBarStart = Vec2(0, m_BodyRange.y / 2);
	auto HPBarEnd = Vec2(m_BodyRange.x, 10.f);
	auto range = Vec2((m_BodyRange.x*(float)m_HP) / (float)m_MaxHP, 10.f);

	char buf[255];
	sprintf(buf, "HP: %d", GetHP());
	m_pLabel->setPosition(HPBarStart + Vec2(0, 20));
	m_pLabel->setScale(3.f);
	m_pLabel->setString(buf);

	MakeBox(HPBarStart, HPBarEnd, RED_BOX_SOLID_TAG);
	MakeBox(HPBarStart, range, GREEN_BOX_SOLID_TAG);
	return 0;
}