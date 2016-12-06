#include "pch.h"
#include "ManageMap.h"
#include "TemporaryDefine.h"


TMXTiledMap* ManageMap::loadMap(const char* MAP_NAME)
{
	m_pMap = TMXTiledMap::create(MAP_NAME);

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
/*
bool ManageMap::checkMap(const Vec2 background, const Vec2 position, const Vec2 unitVec, TMXTiledMap* map)
{
	auto isWall = ManageMap::checkWall(position + unitVec - background, map);


	return true;
}
*/

Vec2 ManageMap::tileCoordForPosition(Vec2 position, TMXTiledMap* map)
{
	auto x = position.x / map->getTileSize().width;
	auto y = ((map->getMapSize().height * map->getTileSize().height) - position.y) / map->getTileSize().height;

	return Vec2((int)x, (int)y);
}

bool ManageMap::checkWall(Vec2 position, TMXTiledMap* map)
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


bool ManageMap::checkChangeMap(Vec2 position, TMXTiledMap* map)
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
