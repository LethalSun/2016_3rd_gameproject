#include "pch.h"
#include "InputLayer.h"
#include "StageOne.h"
#include "ManageMap.h"
#include "ManageMove.h"
#include "TemporaryDefine.h"
#include "PlayerCharacterManager.h"
#include "ManageEnemyMove.h"

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

	// 임시 몬스터
	test_sprite = Sprite::create("TempResourceHW/monster.png");
	test_sprite->setPosition(1000, 1000);
	m_pMap->addChild(test_sprite,3);
	
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

	Vec2 monsterPosition = test_sprite->getPosition();
	monsterPosition = m_pManageEnemyMove->update(monsterPosition, Vec2(1, 0), m_pMap);
	test_sprite->setPosition(monsterPosition);
}