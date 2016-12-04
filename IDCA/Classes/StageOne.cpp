#include "pch.h"
#include "InputLayer.h"
#include "StageOne.h"
#include "ManageMap.h"
#include "ManageMove.h"
#include "TemporaryDefine.h"
#include "PlayerCharacterManager.h"

#include "Character.h"
#include "CharacterManager.h"

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



	m_InputLayer = InputLayer::create();

	m_pPlayerCharacterManager = PlayerCharacterManager::create(PLAYER_FILE_NAME, PLAYER_FILE_EXTENTION);



	/////////////임시 캐릭터///////////////////

	//캐릭터 애드차일드
	m_keyboardInput = 0;
	m_pCharacterManager = CharacterManager::create();
	addChild(m_pCharacterManager);
	m_pCharacter = Character::create(TEMP_DEFINE::ARCH_BISHOP_FILE_NAME, TEMP_DEFINE::SPRITE_FRAME_FILE_EXTENTION);
	m_pCharacter->setPosition(Vec2(100, 400));

	addChild(m_pCharacter);



	/////////////////////////////////////////


	scheduleUpdate();




	return true;
}

void StageOne::update(float delta)
{
	m_pPlayerCharacterManager->GetInput(m_InputLayer->GetInputArray());
	m_pPlayerCharacterManager->GetUnitVac(m_InputLayer->GetInputUnitVec());


	/////////////임시 캐릭터/////
	auto unitVec = Vec2(m_InputLayer->GetInputArray()[0], m_InputLayer->GetInputArray()[1]);	
	auto position = m_pManageMove->update(m_pCharacter->getPosition(), m_background, unitVec, m_pMap);
	m_pCharacter->setPosition(position);
}