#include "pch.h"
#include "CreateMap.h"
#include "TemporaryDefine.h"


TMXTiledMap* CreateMap::loadMap(const char* MAP_NAME)
{
	m_pMap = TMXTiledMap::create(MAP_NAME);

	return m_pMap;
}

bool CreateMap::init()
{
	if (!Layer::init())
	{
		return false;
	}





	return true;
}


