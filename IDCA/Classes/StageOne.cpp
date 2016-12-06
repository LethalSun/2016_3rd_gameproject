#include "pch.h"
#include "InputLayer.h"
#include "StageOne.h"
#include "ManageMap.h"
#include "ManageMove.h"
#include "TemporaryDefine.h"
#include "PlayerCharacterManager.h"
<<<<<<< HEAD

=======
#include "Enemy_Choco.h"
#include "EnemyManager.h"
>>>>>>> Create/Enemy
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
	m_pEnemyManager = m_pEnemyManager->getInstance();
	m_pEnemyManager->setMapPointer(m_pMap);
	m_pEnemyManager->MakeEnemy(ENEMY_TYPE::CHOCO, Vec2(500.f, 650.f));
	m_pEnemyManager->MakeEnemy(ENEMY_TYPE::CHOCO, Vec2(500.f, 750.f));
	addChild(m_pEnemyManager);


	scheduleUpdate();
	return true;
}

void StageOne::update(float delta)
{

	m_pPlayerCharacterManager->GetInput(m_InputLayer->GetInputArray());
	m_pPlayerCharacterManager->GetUnitVac(m_InputLayer->GetInputUnitVec());
	

	int state = m_pPlayerCharacterManager->getState();

	if(state == 0 || state == 2)
	{
		Vec2 position = m_pPlayerCharacterManager->getPlayerPosition();
		Vec2 backgroundposition = m_pMap->getPosition();
		Vec2 unitVec = Vec2(m_InputLayer->GetInputUnitVec()[0],m_InputLayer->GetInputUnitVec()[1]);
		position = m_pManageMove->update(position, backgroundposition, unitVec, m_pMap);
		m_pPlayerCharacterManager->setPlayerPosition(position);
	}
}