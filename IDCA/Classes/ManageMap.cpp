#include "pch.h"
#include "ManageMap.h"
#include "TemporaryDefine.h"
#include "Enemy.h"

TMXTiledMap* ManageMap::loadMap(const char* mapName)
{
	m_pMap = TMXTiledMap::create(mapName);
/*
	auto objectGroup = m_pMap->getObjectGroup("Object layer 1");
	auto startObject = objectGroup->getObject("Start");
	*/
	return m_pMap;
}


bool ManageMap::init()
{
	if (!Layer::init())
	{
		return false;
	}

	
	return true;
}


Vec2 ManageMap::tileCoordForPosition(const Vec2 position, const TMXTiledMap* map)
{
	auto x = position.x / map->getTileSize().width;
	auto y = ((map->getMapSize().height * map->getTileSize().height) - position.y) / map->getTileSize().height;

	return Vec2((int)x, (int)y);
}

bool ManageMap::checkWall(const Vec2 position, const TMXTiledMap* map)
{
	auto tileCoord = tileCoordForPosition(position, map);

	if ((tileCoord.x < 0 || tileCoord.x >= map->getMapSize().width) ||
		(tileCoord.y < 0 || tileCoord.y >= map->getMapSize().height))
	{
		return false;

	}

	auto tileGid1 = map->layerNamed(TEMP_DEFINE::TILELAYER1)->tileGIDAt(tileCoord);
	auto tileGid2 = map->layerNamed(TEMP_DEFINE::TILELAYER2)->tileGIDAt(tileCoord);

	if (tileGid1 == 0 || tileGid2 != 0)
	{
		return false;
	}
			

	return true;

}

bool ManageMap::checkWall(const Vec2 position, const TMXTiledMap* map,Vector<Enemy*>* enemyVector)
{
	auto checkWithMap = true;
	auto checkWithEnemy = true;
	




	auto tileCoord = tileCoordForPosition(position, map);

	if ((tileCoord.x < 0 || tileCoord.x >= map->getMapSize().width) ||
		(tileCoord.y < 0 || tileCoord.y >= map->getMapSize().height))
	{
		checkWithMap = false;

	}

	auto tileGid1 = map->layerNamed(TEMP_DEFINE::TILELAYER1)->tileGIDAt(tileCoord);
	auto tileGid2 = map->layerNamed(TEMP_DEFINE::TILELAYER2)->tileGIDAt(tileCoord);

	if (tileGid1 == 0 || tileGid2 != 0)
	{
		checkWithMap = false;
	}




	for (int i = 0; i < enemyVector->size(); i++)
	{

		Vec2 enemyPosition = enemyVector->at(i)->getPosition();
		auto enemyTileCoord = tileCoordForPosition(enemyPosition, map);

		if (tileCoord == enemyTileCoord)
		{

			for (int j = 0; j <enemyVector->size(); j++)
			{
				auto otherEnemy = enemyVector->at(j);
				auto otherEnemyTileCoord = tileCoordForPosition(otherEnemy->getPosition(), map);

				if (tileCoord == otherEnemyTileCoord&& j!= i)
				{
					checkWithEnemy = false;
				}

			}
		}
	}




	if (checkWithEnemy == false || checkWithMap == false)
	{
		return false;
	}


	return true;

}


bool ManageMap::checkChangeMap(const Vec2 position, const TMXTiledMap* map)
{
	auto tileCoord = tileCoordForPosition(position, map);

	if (tileCoord.x < 0 || tileCoord.x >= map->getMapSize().width ||
		tileCoord.y < 0 || tileCoord.y >= map->getMapSize().height)
	{
		return false;
	}

	auto tileGid = map->layerNamed(TEMP_DEFINE::TILELAYER5)->tileGIDAt(tileCoord);
	
	if (tileGid != 0)
	{
		return true;
	}

	return false;
}
