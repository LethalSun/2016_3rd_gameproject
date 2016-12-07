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

void CollideManager::SetBackGroundPosition(Vec2 backgroundPosition)
{
	m_BackgroundPosition = backgroundPosition;
}

void CollideManager::SetCMEnemyPointer(Vector<Enemy*>* enemyVector)
{
	m_pvEnemy = enemyVector;
}

void CollideManager::update(float dt)
{
}