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

	//addChild(m_pMap);
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(TEMP_DEFINE::PLIST_NAME_2);
	m_InputLayer = InputLayer::create();

	addChild(m_InputLayer);
	m_pPlayerCharacterManager = PlayerCharacterManager::create(PLAYER_FILE_NAME, PLAYER_FILE_EXTENTION);
	addChild(m_pPlayerCharacterManager);

	/////////////임시 캐릭터///////////////////

	//캐릭터 애드차일드
	m_keyboardInput = 0;
	m_pCharacterManager = CharacterManager::create();
	addChild(m_pCharacterManager);
	m_pCharacter = Character::create(TEMP_DEFINE::ARCH_BISHOP_FILE_NAME, TEMP_DEFINE::SPRITE_FRAME_FILE_EXTENTION);
	m_pCharacter->setPosition(Vec2(100, 400));

	addChild(m_pCharacter);

	/////////////////////////////////////////

	m_pPlayerCharacterManager->GetInput(m_InputLayer->GetInputArray());
	m_pPlayerCharacterManager->GetUnitVac(m_InputLayer->GetInputUnitVec());

	scheduleUpdate();
	return true;
}

void StageOne::update(float delta)
{
	auto input = m_InputLayer->GetInputArray();
	auto unitVecC = m_InputLayer->GetInputUnitVec();

	m_pPlayerCharacterManager->GetInput(input);
	m_pPlayerCharacterManager->GetUnitVac(unitVecC);

	/////////////임시 캐릭터/////
	auto unitVec = Vec2(m_InputLayer->GetInputUnitVec()[0], m_InputLayer->GetInputUnitVec()[1]);
	m_pCharacter->SetInput(m_keyboardInput);
	m_pCharacterManager->GetCharacterInfo(m_pCharacter);

	m_pManageMove->update(m_pCharacter->getPosition(), m_background, unitVec, m_pMap);
}