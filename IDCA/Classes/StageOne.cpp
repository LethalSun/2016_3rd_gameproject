#include "pch.h"
#include "InputLayer.h"
#include "StageOne.h"
#include "CreateMap.h"
#include "TemporaryDefine.h"
#include "PlayerCharacterManager.h"
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

	//auto cm = CreateMap::create();
	//m_pMap = TMXTiledMap::create(TEMP_DEFINE::MAP_NAME1);
	//m_pMap = cm->loadMap(TEMP_DEFINE::MAP_NAME1);

	//addChild(m_pMap);
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(TEMP_DEFINE::PLIST_NAME_2);
	m_InputLayer = InputLayer::create();

	addChild(m_InputLayer);
	m_pPlayerCharacterManager = PlayerCharacterManager::create(PLAYER_FILE_NAME, PLAYER_FILE_EXTENTION);
	addChild(m_pPlayerCharacterManager);
	return true;
}

void StageOne::update(float delta)
{
	m_pPlayerCharacterManager->GetInput(m_InputLayer->GetInputArray());
	m_pPlayerCharacterManager->GetUnitVac(m_InputLayer->GetInputUnitVec());
}