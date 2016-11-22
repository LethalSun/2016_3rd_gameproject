#include "pch.h"
#include "createMap.h"
#include "TemporaryDefine.h"

createMap::createMap()
{

}


createMap::~createMap()
{
}


CCTMXTiledMap* createMap::create(const char* MAPNAME_1)
{

	newMap = CCTMXTiledMap::create(MAPNAME_1);
	background_layer1 = newMap->layerNamed(TEMP_DEFINE::TILELAYER_1);
	background_layer2 = newMap->layerNamed(TEMP_DEFINE::TILELAYER_2);
	background_layer3 = newMap->layerNamed(TEMP_DEFINE::TILELAYER_3);
	background_layer4 = newMap->layerNamed(TEMP_DEFINE::TILELAYER_4);
	background_layer5 = newMap->layerNamed(TEMP_DEFINE::TILELAYER_5);

	return newMap;
}