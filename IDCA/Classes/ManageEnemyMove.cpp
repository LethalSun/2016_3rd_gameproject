#include "pch.h"
#include "ManageEnemyMove.h"
#include "ManageMap.h"
#include "TemporaryDefine.h"
#include "Enemy.h"
#include "EnemyManager.h"

bool ManageEnemyMove::init()
{
	if (!Node::init())
	{
		return false;
	}

	//m_EnemyManager = EnemyManager::getInstance();
	return true;
}


Vec2 ManageEnemyMove::update(Vec2 position, Vec2 unitVec, TMXTiledMap* map, const float dt,Enemy* enemy)
{
	m_EnemyManager = EnemyManager::getInstance();
	m_pManageMap = ManageMap::create();
	enemyVector = m_EnemyManager->getEnemyVector();

	auto movable = false;

	movable = m_pManageMap->checkWall(position + (unitVec)*5, map, enemyVector);



	if (movable == true)
	{
		position += unitVec * enemy->getMoveSpeed();
	}

	if (movable == false) CCLOG("ManageEnemyMove::update -> moveable is false!");
	if (movable == true) CCLOG("ManageEnemyMove::update -> moveable is true.");
	return position;
}

