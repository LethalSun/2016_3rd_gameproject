#include "pch.h"
#include "CollideManager.h"
#include "Enemy.h"
#include "Enemy_Atroce.h"
#include "Enemy_Choco.h"
#include "PlayerCharacter.h"
#include "EnemyManager.h"

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
	CheckMonsterAttack();
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

//캐릭터->몬스터 공격체크
void CollideManager::CheckCharacterAttack()
{
	SetCMEnemyPointer(EnemyManager::getInstance()->getEnemyVector());
	if (m_pPlayerCharacter->GetState() != STATE::ATTACK)
	{
		return;
	}

	if (m_pPlayerCharacter->IsAttackChecked() == true)
	{
		return;
	}

	// TODO :: Enemy를 지우면 여기서 자꾸 충돌이 일어나는데 어떻게 해결해야 할지?
	Vector<Enemy*>::iterator iter = m_pvEnemy->begin();
	for (; iter != m_pvEnemy->end(); ++iter)
	{
		// X collide
		auto xMin = m_pPlayerCharacter->GetAttackRange().x / 2
			+ (*iter)->getBodyRangeForCollide().x / 2;

		auto x = AbsFloat(m_pPlayerCharacter->GetAttackAnchorPoint().x,
			(*iter)->getBodyAnchorPoint().x);
		// Y collide
		auto yMin = m_pPlayerCharacter->GetAttackRange().y / 2
			+ (*iter)->getBodyRangeForCollide().y / 2;
		auto y = AbsFloat(m_pPlayerCharacter->GetAttackAnchorPoint().y,
			(*iter)->getBodyAnchorPoint().y);

		if ((xMin >= x) && (yMin >= y))
		{
			//TODO:아침에 일어나서 혼자 머지 하다가 일단 수정함그런데 혹시나 해서 양쪽 코드 주석 달아놓음의견묻고 지울것
			//auto curHP = (*iter)->getHP();
			//curHP = curHP - m_pPlayerCharacter->GetDamage();
			//(*iter)->setHP(curHP);
			//m_pPlayerCharacter->SetAttackChecked();
			//break;

			//int damage = m_pPlayerCharacter->GetDamage();
			//(*iter)->setAttackedDamage(damage);
			auto damage = m_pPlayerCharacter->GetDamage();
			(*iter)->setAttackedDamage(damage);
			m_pPlayerCharacter->SetAttackChecked();
			//break;
		}
	}

}
//몬스터->캐릭터 공격체크
void CollideManager::CheckMonsterAttack()
{
	Vector<Enemy*>::iterator iter = m_pvEnemy->begin();
	for (; iter != m_pvEnemy->end(); ++iter)
	{
		if ((*iter)->getState()->returnStateNumber() != ENEMY_STATE_TYPE::ATTACKING)
		{
			continue;
		}
		if ((*iter)->getAttackChecked() == true)
		{
			continue;
		}

		// X collide
		auto xMin = m_pPlayerCharacter->GetBodyRange().x / 2
			+ (*iter)->getAttackRangeForCollide().x / 2;

		auto x = AbsFloat(m_pPlayerCharacter->GetBodyAnchorPoint().x,
			(*iter)->getAttackAnchorPoint().x);
		// Y collide
		auto yMin = m_pPlayerCharacter->GetBodyRange().y / 2
			+ (*iter)->getAttackRangeForCollide().y / 2;
		auto y = AbsFloat(m_pPlayerCharacter->GetBodyAnchorPoint().y,
			(*iter)->getAttackAnchorPoint().y);
		if ((xMin >= x) && (yMin >= y))
		{
			(*iter)->setAttackChecked(true);
			CCLOG("Attacked!");
		}
	}
}