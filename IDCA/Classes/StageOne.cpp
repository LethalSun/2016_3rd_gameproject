#include "pch.h"
#include "InputLayer.h"
#include "StageOne.h"
#include "ManageMap.h"
#include "ManageMove.h"
#include "Define.h"
#include "PlayerCharacterManager.h"
#include "ManageEnemyMove.h"
#include "Enemy_Choco.h"
#include "EnemyManager.h"
#include "SimpleAudioEngine.h"
#include "CollideManager.h"

const char BGM[] = "Sound/Forbidden.mp3";

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

	// ����� ���.
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(BGM, true);

	//�� ���� ���
	m_pManageMap = ManageMap::create();
	m_pMap = m_pManageMap->loadMap(TEMP_DEFINE::MAP_NAME1);
	addChild(m_pMap);

	

	//�̵� ���� ���
	m_pManageMove = ManageMove::create();
	m_pManageEnemyMove = ManageEnemyMove::create();

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(TEMP_DEFINE::PLIST_NAME_2);
	m_InputLayer = InputLayer::create();
	addChild(m_InputLayer);

	m_pPlayerCharacterManager = PlayerCharacterManager::create(PLAYER_FILE_NAME, PLAYER_FILE_EXTENTION);
	addChild(m_pPlayerCharacterManager);

	m_pPlayerCharacterManager->GetInput(m_InputLayer->GetInputArray());
	m_pPlayerCharacterManager->GetUnitVac(m_InputLayer->GetInputUnitVec());

	//�浹�Ŵ��� ���
	m_pCollideManager = CollideManager::create();
	m_pCollideManager->SetPlayerCharacterPointer(m_pPlayerCharacterManager->GetCharacter());
	m_pCollideManager->SetCMEnemyPointer(m_pEnemyManager->getEnemyVector());
	addChild(m_pCollideManager);

	// EnemyManager ���
	m_pEnemyManager = m_pEnemyManager->getInstance();
	m_pEnemyManager->setMapPointer(m_pMap);
	m_pEnemyManager->setInnerCollideManager(m_pCollideManager);
	//m_pEnemyManager->StageOneSetting();
	m_pEnemyManager->SummonAncientTree();

	//�ӽ� ������ �ڵ�

	//�ӽ� �������ڵ� ��
	scheduleUpdate();
	return true;
}

void StageOne::update(float delta)
{
	m_pPlayerCharacterManager->GetInput(m_InputLayer->GetInputArray());
	m_pPlayerCharacterManager->GetUnitVac(m_InputLayer->GetInputUnitVec());
	int state = m_pPlayerCharacterManager->getState();
	Vec2 position = m_pPlayerCharacterManager->getPlayerPosition();
	position = m_pPlayerCharacterManager->getPlayerPosition();

	if (state == 0 || state == 2)
	{
		Vec2 backgroundposition = m_pMap->getPosition();
		Vec2 unitVec = Vec2(m_InputLayer->GetInputUnitVec()[0], m_InputLayer->GetInputUnitVec()[1]);
		position = m_pManageMove->update(position, backgroundposition, unitVec, m_pMap);
		m_pPlayerCharacterManager->setPlayerPosition(position, backgroundposition);
	}

	// EnemyManager
	m_pEnemyManager->ProvidePlayerPosition(position - m_pMap->getPosition());
	m_pEnemyManager->StageOneTriggerCheck();
	m_pEnemyManager->DieCheck();

	return;
}