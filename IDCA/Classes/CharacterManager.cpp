#include "pch.h"
#include "CharacterManager.h"
#include "character.h"
#include "TemporaryDefine.h"
#define DEBUG_RED_BOX

bool CharacterManager::init()
{
	if (!Node::init())
	{
		return false;
	}

	//멤버 변수 초기화
	m_CharacterPosition = Vec2(0, 0);
	m_CharacterAttackDirection = Vec2(0, 0);
	m_CharacterAttackRange = Vec2(0, 0);
	m_TargetPosition = Vec2(0, 0);
	m_HitHit = false;

	//캐릭터와 몬스터의 공격범위와 피격범위를 없에기 위한 태그
	m_BoxTagMonster = TEMP_DEFINE::BOX_TAG_MONSTER;
	m_BoxTagCharacter = TEMP_DEFINE::BOX_TAG_CHARACTER;

	//공격한번에 hp가 여러번감소하는것을 방지하기위해서  캐릭터의 상태를 받는다.
	m_CharacterBeforstate = TEMP_DEFINE::CHARACTER_STATE::STATE_STOP;
	m_CharacterState = TEMP_DEFINE::CHARACTER_STATE::STATE_STOP;

	scheduleUpdate();

	return true;
}

void CharacterManager::update(float delta)
{
	char buffer[100];
	m_HitHit = false;

	if (m_CharacterState == TEMP_DEFINE::CHARACTER_STATE::STATE_ATTACK && m_CharacterBeforstate != TEMP_DEFINE::CHARACTER_STATE::STATE_ATTACK)
	{
		m_HitHit = CheckHit();
	}

	m_CharacterBeforstate = m_CharacterState;
}

void CharacterManager::GetCharacterInfo(Character * character)
{
	m_CharacterPosition = character->getPosition();
	m_CharacterAttackDirection = character->GetCurrentDitection();
	m_CharacterAttackRange = character->GetAttackRange();
	m_CharacterState = character->GetCharacterState();

	m_CharacterBeAttackedBox.x = character->getContentSize().width;
	m_CharacterBeAttackedBox.y = character->getContentSize().height;

	auto attackAnchorPoint = AttackAnchorPoint();

	//타격범위 표시
#ifdef DEBUG_RED_BOX
	MakeRedBox(attackAnchorPoint, m_CharacterAttackRange, m_BoxTagCharacter);
#endif // DEBUD_RED_BOX
}

void CharacterManager::GetSpriteInfo(Sprite * sprite)
{
	m_TargetPosition = sprite->getPosition();

	m_TargetBeAttackefBox.x = sprite->getContentSize().width;
	m_TargetBeAttackefBox.y = sprite->getContentSize().height;
	//피격범위
#ifdef DEBUG_RED_BOX
	MakeRedBox(m_TargetPosition, m_TargetBeAttackefBox, m_BoxTagMonster);
#endif // DEBUD_RED_BOX
}

bool CharacterManager::CheckHit()
{
	auto attackAnchorPoint = AttackAnchorPoint();
	auto checkingDistance = Distance(attackAnchorPoint, m_TargetPosition);
	bool hit = true;

	if (checkingDistance.x > (m_CharacterAttackRange.x / 2 + m_TargetBeAttackefBox.x / 2))
	{
		hit = false;
		return hit;
	}

	if (checkingDistance.y > (m_CharacterAttackRange.y / 2 + m_TargetBeAttackefBox.y / 2))
	{
		hit = false;
		return hit;
	}

	return hit;
}

bool CharacterManager::GetHitInfo()
{
	bool result = m_HitHit;

	return result;
}

void CharacterManager::MakeRedBox(Vec2 position, Vec2 boxInfo, int tag)
{
	if (getChildByTag(tag) != nullptr)
	{
		removeChildByTag(tag);
	}
	Vec2 vertex[4] = { Vec2(position.x - boxInfo.x / 2,position.y - boxInfo.y / 2),
						Vec2(position.x + boxInfo.x / 2,position.y + boxInfo.y / 2) };

	auto box = DrawNode::create();
	box->drawRect(vertex[0], vertex[1], Color4F(1.0f, 0.0f, 0.0f, 1.0f));
	addChild(box, 0, tag);
}

Vec2 CharacterManager::Distance(Vec2 a, Vec2 b)
{
	//두 점의 거리를 구한다.
	auto x = ((a.x - b.x) < 0) ? -(a.x - b.x) : (a.x - b.x);
	auto y = ((a.y - b.y) < 0) ? -(a.y - b.y) : (a.y - b.y);
	return Vec2(x, y);
}

Vec2 CharacterManager::AttackAnchorPoint()
{
	//공격범위의 중심
	auto x = m_CharacterPosition.x +
		m_CharacterAttackDirection.x*(m_CharacterBeAttackedBox.x / 2 + m_CharacterAttackRange.x / 2)*0.5;

	auto y = m_CharacterPosition.y +
		m_CharacterAttackDirection.y*(m_CharacterBeAttackedBox.y / 2 + m_CharacterAttackRange.y / 2)*0.5;

	return Vec2(x, y);
}