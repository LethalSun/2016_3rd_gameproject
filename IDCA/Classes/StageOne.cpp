#include "pch.h"
#include "InputLayer.h"
#include "StageOne.h"
#include "CreateMap.h"
#include "TemporaryDefine.h"



Scene * StageOne::createScene()
{
	auto scene = Scene::create();
	auto layer = StageOne::create();
	scene->addChild(layer);

	return scene;
}

StageOne * StageOne::create()
{
	StageOne* pRet = new(std::nothrow)StageOne();
	if (pRet && pRet->init())
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = nullptr;
		return nullptr;
	}
}

bool StageOne::init()
{
	if (!Layer::init())
	{
		return false;
	}
	

	//
	auto map = CreateMap::create();
	m_pMap = map->loadMap(TEMP_DEFINE::MAP_NAME1);
	m_pBackground.push_back(m_pMap->layerNamed(TEMP_DEFINE::TILELAYER1));
	m_pBackground.push_back(m_pMap->layerNamed(TEMP_DEFINE::TILELAYER2));
	m_pBackground.push_back(m_pMap->layerNamed(TEMP_DEFINE::TILELAYER3));
	m_pBackground.push_back(m_pMap->layerNamed(TEMP_DEFINE::TILELAYER4));
	m_pBackground.push_back(m_pMap->layerNamed(TEMP_DEFINE::TILELAYER5));

	m_mapSize = m_pMap->getMapSize();
	m_winSize = Director::getInstance()->getWinSize();
	m_tileSize = m_pMap->getTileSize();

	addChild(m_pMap);

	m_InputLayer = InputLayer::create();
	return true;
}


void StageOne::update(float delta)
{
	Vec2 unitVec = (m_InputLayer->m_Input[0], m_InputLayer->m_InputArray[1]);
}