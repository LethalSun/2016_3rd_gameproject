#include "pch.h"
#include "InputLayer.h"
#include "StageOne.h"
#include "ManageMap.h"
#include "ManageMove.h"
#include "TemporaryDefine.h"
#include "PlayerCharacterManager.h"
#include "ManageEnemyMove.h"
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
	addChild(m_pMap);
	//이동 관리 등록
	m_pManageMove = ManageMove::create();
	m_pManageEnemyMove = ManageEnemyMove::create();
	
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
	m_pEnemyManager->MakeEnemy(ENEMY_TYPE::ATROCE, Vec2(700.f, 650.f));
	addChild(m_pEnemyManager);


	scheduleUpdate();
	return true;
}

void StageOne::update(float delta)
{

	m_pPlayerCharacterManager->GetInput(m_InputLayer->GetInputArray());
	m_pPlayerCharacterManager->GetUnitVac(m_InputLayer->GetInputUnitVec());
	

	int state = m_pPlayerCharacterManager->getState();
	Vec2 position;

	position = m_pPlayerCharacterManager->getPlayerPosition();

	if(state == 0 || state == 2)
	{
		Vec2 backgroundposition = m_pMap->getPosition();
		Vec2 unitVec = Vec2(m_InputLayer->GetInputUnitVec()[0],m_InputLayer->GetInputUnitVec()[1]);
		position = m_pManageMove->update(position, backgroundposition, unitVec, m_pMap);
		m_pPlayerCharacterManager->setPlayerPosition(position);
	}

	char buf[255];
	sprintf(buf, "[Player] X : %f, Y : %f", position.x, position.y);
	CCLOG(buf);
	m_pEnemyManager->ProvidePlayerPosition(position - m_pMap->getPosition());
	// TODO :: PlayerPosition을 지금 맵에 따라서 달라지는 값으로 받고 있음.
	// Enemy는 절대적인 좌표값을 받아야 함.
	
}