#include "pch.h"
#include "CollideManager.h"
#include "Enemy.h"
#include "Enemy_Atroce.h"
#include "Enemy_Choco.h"
#include "PlayerCharacter.h"

CollideManager::CollideManager()
{
}

CollideManager::~CollideManager()
{
}

CollideManager * CollideManager::create()
{
	auto pMaker = new(std::nothrow) CollideManager();
	if (pMaker&&pMaker->init())
	{
		pMaker->autorelease();
		return pMaker;
	}
	else
	{
		delete pMaker;
		pMaker = nullptr;
		return pMaker;
	}
}

bool CollideManager::init()
{
	if (!(Node::init()))
	{
		return false;
	}

	m_pvEnemy = nullptr;
	m_pPlayerCharacter = nullptr;
	m_BackgroundPosition = Vec2(0, 0);
	scheduleUpdate();

	return true;
}

void CollideManager::SetPlayerCharacterPointer(PlayerCharacter * playerCharacter)
{
	m_pPlayerCharacter = playerCharacter;
}

void CollideManager::SetCMEnemyPointer(Vector<Enemy*>& enemyVector)
{
	m_pvEnemy = &enemyVector;
}

void CollideManager::update(float dt)
{
	CheckCollide();
}

void CollideManager::CheckCollide()
{
	//캐릭터 공격 체크
	CheckCharacterAttack();
}

float CollideManager::AbsFloat(float f1, float f2)
{
	float fr;
	if (f1 > f2)
	{
		fr = f1 - f2;
	}
	else
	{
		fr = f2 - f1;
	}
	return fr;
}

void CollideManager::CheckCharacterAttack()
{
	if (m_pPlayerCharacter->GetState() != STATE::ATTACK)
	{
		return;
	}

	if (m_pPlayerCharacter->IsAttackChecked() == true)
	{
		return;
	}

	Vector<Enemy*>::iterator iter = m_pvEnemy->begin();
	for (; iter != m_pvEnemy->end(); ++iter)
	{
		// X collide
		auto xMin = m_pPlayerCharacter->GetAttackRange().x / 2
			+ (*iter)->getAttackRangeForCollide().x / 2;

		auto x = AbsFloat(m_pPlayerCharacter->GetAttackAnchorPoint().x,
			(*iter)->getBodyAnchorPoint().x);
		// Y collide
		auto yMin = m_pPlayerCharacter->GetAttackRange().y / 2
			+ (*iter)->getAttackRangeForCollide().y / 2;
		auto y = AbsFloat(m_pPlayerCharacter->GetAttackAnchorPoint().y,
			(*iter)->getBodyAnchorPoint().y);

		if ((xMin >= x) && (yMin >= y))
		{
			auto curHP = (*iter)->getHP();
			curHP = curHP - m_pPlayerCharacter->GetDamage();
			(*iter)->setHP(curHP);
			m_pPlayerCharacter->SetAttackChecked();
			break;
		}
	}
}