#include "pch.h"
#include "CharacterScene.h"
#include "Character.h"
#include "CharacterManager.h"
#include "TemporaryDefine.h"
#include <bitset>

Scene * CharacterScene::createScene()
{
	auto scene = Scene::createWithPhysics();
	auto layer = CharacterScene::create();
	scene->addChild(layer);

	return scene;
}

bool CharacterScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	//변수 초기화
	m_keyboardInput = 0;
	m_pCharacterManager = CharacterManager::create();
	addChild(m_pCharacterManager);
	//캐릭터 애드차일드
	m_pCharacter = Character::create(TEMP_DEFINE::ARCH_BISHOP_FILE_NAME, TEMP_DEFINE::SPRITE_FRAME_FILE_EXTENTION);
	m_pCharacter->setPosition(Vec2(100, 100));
	addChild(m_pCharacter);
	//이성경 애드차일드
	m_pMonster = Sprite::create("TempResourceHW/lSG.png");
	m_pMonster->setPosition(Vec2(900, 600));
	auto action1 = MoveTo::create(20, Vec2(100, 600));
	auto action2 = MoveTo::create(20, Vec2(900, 600));
	auto seq = Sequence::create(action1, action2, nullptr);
	auto repeat = RepeatForever::create(seq);
	m_pMonster->runAction(repeat);
	addChild(m_pMonster);
	//몬스터1 애드차일드
	m_pMonster1 = Sprite::create("TempResourceHW/monster.png");
	m_pMonster1->setPosition(Vec2(900, 100));
	auto action3 = MoveTo::create(8, Vec2(500, 100));
	auto action4 = MoveTo::create(8, Vec2(900, 100));
	auto seq1 = Sequence::create(action3, action4, nullptr);
	auto repeat1 = RepeatForever::create(seq1);
	m_pMonster1->runAction(repeat1);
	addChild(m_pMonster1);
	//이벤트 리스너
	auto eventListener = EventListenerKeyboard::create();
	eventListener->onKeyPressed = CC_CALLBACK_2(CharacterScene::onKeyPressed, this);
	eventListener->onKeyReleased = CC_CALLBACK_2(CharacterScene::onKeyReleased, this);
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, this);
	//씬전환
	auto origin = Director::getInstance()->getVisibleOrigin();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto changeScene = MenuItemImage::create("TempResourceHW/back.png", "TempResourceHW/backC.png", CC_CALLBACK_1(CharacterScene::menuBackCallback, this));
	changeScene->setPosition(Vec2(origin.x + visibleSize.width - changeScene->getContentSize().width / 2,
		origin.y + changeScene->getContentSize().height / 2));
	// create menu, it's an autorelease object
	auto menu = Menu::create(changeScene, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);
	//업데이트 함수 등록
	this->scheduleUpdate();
	return true;
}

void CharacterScene::update(float delta)
{
	m_pCharacter->SetInput(m_keyboardInput);
	m_pCharacterManager->GetCharacterInfo(m_pCharacter);
	//피격효과

	if (m_pMonster != nullptr)
	{
		m_pCharacterManager->GetSpriteInfo(m_pMonster);
		bool hit = false;

		hit = m_pCharacterManager->GetHitInfo();

		char buffer[100];
		sprintf(buffer, "hit = %d", hit);
		cocos2d::log(buffer);

		if (hit == true)
		{
			m_pCharacter->SetHP(1);
			//
		}

		if (m_pCharacter->GetCharacterHP() == 0)//작거나 같다로해야함 만약에 데미지를 크게 입어서 음수가 되면?
		{
			m_pMonster->removeFromParent();
			m_pMonster = nullptr;
		}
	}
}

void CharacterScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event * event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW)
	{
		m_keyboardInput |= TEMP_DEFINE::INPUT::KEY_UP;
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW)
	{
		m_keyboardInput |= TEMP_DEFINE::INPUT::KEY_DOWN;
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
	{
		m_keyboardInput |= TEMP_DEFINE::INPUT::KEY_RIGHT;
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
	{
		m_keyboardInput |= TEMP_DEFINE::INPUT::KEY_LEFT;
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_A)
	{
		m_keyboardInput |= TEMP_DEFINE::INPUT::KEY_A;
	}
}

void CharacterScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event * event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW)
	{
		m_keyboardInput &= ~(TEMP_DEFINE::INPUT::KEY_UP);
	}

	else if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW)
	{
		m_keyboardInput &= ~(TEMP_DEFINE::INPUT::KEY_DOWN);
	}

	else if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
	{
		m_keyboardInput &= ~(TEMP_DEFINE::INPUT::KEY_RIGHT);
	}

	else if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
	{
		m_keyboardInput &= ~(TEMP_DEFINE::INPUT::KEY_LEFT);
	}

	else if (keyCode == EventKeyboard::KeyCode::KEY_A)
	{
		m_keyboardInput &= ~(TEMP_DEFINE::INPUT::KEY_A);
	}
}

void CharacterScene::menuBackCallback(cocos2d::Ref * pSender)
{
	Director::getInstance()->popScene();
}

CharacterScene::CharacterScene()
{
}

CharacterScene::~CharacterScene()
{
}