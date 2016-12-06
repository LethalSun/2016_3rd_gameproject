#include "pch.h"
#include "InputLayer.h"
#include "StageOne.h"
#include "ManageMap.h"
#include "ManageMove.h"
#include "TemporaryDefine.h"
#include "PlayerCharacterManager.h"
#include "Enemy_Choco.h"
#include "EnemyManager.h"
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

	//맵 정보 등록
	m_pManageMap = ManageMap::create();
	m_pMap = m_pManageMap->loadMap(TEMP_DEFINE::MAP_NAME1);

	m_mapSize = m_pMap->getMapSize();
	m_winSize = Director::getInstance()->getWinSize();
	m_tileSize = m_pMap->getTileSize();
	m_background = Vec2(0, 0);

	addChild(m_pMap);
	//이동 관리 등록
	m_pManageMove = ManageMove::create();

	//addChild(m_pMap);
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(TEMP_DEFINE::PLIST_NAME_2);
	m_InputLayer = InputLayer::create();

	addChild(m_InputLayer);
	m_pPlayerCharacterManager = PlayerCharacterManager::create(PLAYER_FILE_NAME, PLAYER_FILE_EXTENTION);
	addChild(m_pPlayerCharacterManager);

	m_pPlayerCharacterManager->GetInput(m_InputLayer->GetInputArray());
	m_pPlayerCharacterManager->GetUnitVac(m_InputLayer->GetInputUnitVec());

	// EnemyManager 등록
	m_pEnemy = Enemy_Choco::create(Vec2(500.f, 500.f));
	addChild(m_pEnemy);


	scheduleUpdate();
	return true;
}

void StageOne::update(float delta)
{
	auto input = m_InputLayer->GetInputArray();
	auto unitVecC = m_InputLayer->GetInputUnitVec();

	m_pPlayerCharacterManager->GetInput(input);
	m_pPlayerCharacterManager->GetUnitVac(unitVecC);
}