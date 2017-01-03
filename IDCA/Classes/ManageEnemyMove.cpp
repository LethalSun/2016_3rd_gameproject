#include "pch.h"
#include "ManageEnemyMove.h"
#include "ManageMap.h"
#include "TemporaryDefine.h"
#include "Enemy.h"
#include "EnemyManager.h"

bool ManageEnemyMove::init()
{
	if (!Component::init())
	{
		return false;
	}
	this->setName("Enemy Mover Component");
	m_EnemyManager = m_EnemyManager->getInstance();

	return true;
}



Vec2 ManageEnemyMove::update(Vec2 position, Vec2 unitVec, TMXTiledMap* map, const float dt,Enemy* enemy)
{
	m_pManageMap = ManageMap::create();
	auto enemyVector = &m_EnemyManager->getEnemyVector();

	for (int i = 0; i < enemyVector->size(); i++)
	{
		auto temp_enemy = enemyVector->at(i);
		if (temp_enemy->getHP() <= 0)
		{
			temp_enemy->getMapPointer()->removeChild(temp_enemy);
			
		}
	}

	auto movable = false;
	auto checkCurrent = false;

	checkCurrent = m_pManageMap->checkBlocked(position, Vec2(0, 0), map, enemyVector);
	
	if (checkCurrent == false)
	{
		return position + unitVec * enemy->getMoveSpeed();
	}

	movable = m_pManageMap->checkBlocked(position,unitVec, map, enemyVector);



	if (movable == true)
	{
		position += unitVec * enemy->getMoveSpeed();
	}

	return position;
}

