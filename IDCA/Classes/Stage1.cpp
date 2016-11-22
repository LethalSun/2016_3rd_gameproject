#include "pch.h"
#include "Stage1.h"
#include "Character.h"
#include "CharacterManager.h"
#include "TemporaryDefine.h"
#include <bitset>

Scene * Stage1::createScene()
{
	auto scene = Scene::createWithPhysics();
	auto layer = Stage1::create();
	scene->addChild(layer);

	return scene;
}

bool Stage1::init()
{
	if (!Layer::init())
	{
		return false;
	}
	//변수 초기화
	m_keyboardInput = 0;
	m_pCharacterManager = CharacterManager::create();
	addChild(m_pCharacterManager);
	winSize = Director::getInstance()->getWinSize();

	//이성경 애드차일드
	m_pMonster = Sprite::create("TempResourceHW/lSG.png");
	m_pMonster->setPosition(Vec2(900, 600));
	auto action1 = MoveTo::create(20, Vec2(100, 600));
	auto action2 = MoveTo::create(20, Vec2(900, 600));
	auto seq = Sequence::create(action1, action2, nullptr);
	auto repeat = RepeatForever::create(seq);
	m_pMonster->runAction(repeat);
	addChild(m_pMonster,2);
	


	//이벤트 리스너
	auto eventListener = EventListenerKeyboard::create();
	eventListener->onKeyPressed = CC_CALLBACK_2(Stage1::onKeyPressed, this);
	eventListener->onKeyReleased = CC_CALLBACK_2(Stage1::onKeyReleased, this);
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, this);
	
	
	/*
	//씬전환
	auto origin = Director::getInstance()->getVisibleOrigin();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto changeScene = MenuItemImage::create("TempResourceHW/back.png", "TempResourceHW/backC.png", CC_CALLBACK_1(Stage1::menuBackCallback, this));
	changeScene->setPosition(Vec2(origin.x + visibleSize.width - changeScene->getContentSize().width / 2,
		origin.y + changeScene->getContentSize().height / 2));
	*/
	//업데이트 함수 등록

	map = CCTMXTiledMap::create(TEMP_DEFINE::MAPNAME_1);
	background1 = map->layerNamed(TEMP_DEFINE::TILELAYER_1);
	background2 = map->layerNamed(TEMP_DEFINE::TILELAYER_2);
	background3 = map->layerNamed(TEMP_DEFINE::TILELAYER_3);
	background4 = map->layerNamed(TEMP_DEFINE::TILELAYER_4);
	background5 = map->layerNamed(TEMP_DEFINE::TILELAYER_5);
	auto objectGroup = map->getObjectGroup(TEMP_DEFINE::OBJECTLAYER_1);

	map->setTag(2);
	mapSize = map->getMapSize();
	tileSize = map->getContentSize();
	addChild(map, 1);

	auto objectStart = objectGroup->getObject(TEMP_DEFINE::START_OBJECT);
	auto x = objectStart["x"].asFloat();
	auto y = objectStart["y"].asFloat();


	//캐릭터 애드차일드
	m_pCharacter = Character::create(TEMP_DEFINE::ARCH_BISHOP_FILE_NAME, TEMP_DEFINE::SPRITE_FRAME_FILE_EXTENTION);
	m_pCharacter->setPosition(Vec2(x, y));
	m_pCharacter->setTag(0);
	addChild(m_pCharacter, 2);

	this->scheduleUpdate();
	return true;
}

void Stage1::update(float delta)
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


	auto position = m_pCharacter->getPosition();
	Vec2 moveVec = Vec2(0, 0);
	auto movable = false;
	auto mapChange = false;

	mapChange = checkChangeMap(position);

	if (mapChange == true)
	{
		changeMap();
		return;
	}

	if (isLeft)
	{
		moveVec.add(Vec2(-1, 0));
	}
	else if (isRight)
	{
		moveVec.add(Vec2(1, 0));
	}

	if (isDown)
	{
		moveVec.add(Vec2(0, -1));
	}
	else if (isUp)
	{
		moveVec.add(Vec2(0, 1));
	}

	movable = IsWall(position + moveVec * 16);

	if (movable == true && moveVec != Vec2(0, 0))
	{
		position = setCharacterPosition(position, moveVec);
	}

	map->setPosition(Vec2(backgroundX, backgroundY));
	m_pCharacter->setPosition(position);
	
}

void Stage1::onKeyPressed(EventKeyboard::KeyCode keyCode, Event * event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW)
	{
		m_keyboardInput |= TEMP_DEFINE::INPUT::KEY_UP;
		isUp = true;
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW)
	{
		m_keyboardInput |= TEMP_DEFINE::INPUT::KEY_DOWN;
		isDown = true;
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
	{
		m_keyboardInput |= TEMP_DEFINE::INPUT::KEY_RIGHT;
		isRight = true;
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
	{
		m_keyboardInput |= TEMP_DEFINE::INPUT::KEY_LEFT;
		isLeft = true;
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_A)
	{
		m_keyboardInput |= TEMP_DEFINE::INPUT::KEY_A;
	}
}

void Stage1::onKeyReleased(EventKeyboard::KeyCode keyCode, Event * event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW)
	{
		m_keyboardInput &= ~(TEMP_DEFINE::INPUT::KEY_UP);
		isUp = false;
	}

	else if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW)
	{
		m_keyboardInput &= ~(TEMP_DEFINE::INPUT::KEY_DOWN);
		isDown = false;
	}

	else if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
	{
		m_keyboardInput &= ~(TEMP_DEFINE::INPUT::KEY_RIGHT);
		isRight = false;
	}

	else if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
	{
		m_keyboardInput &= ~(TEMP_DEFINE::INPUT::KEY_LEFT);
		isLeft = false;
	}

	else if (keyCode == EventKeyboard::KeyCode::KEY_A)
	{
		m_keyboardInput &= ~(TEMP_DEFINE::INPUT::KEY_A);
	}
}

void Stage1::menuBackCallback(cocos2d::Ref * pSender)
{
	Director::getInstance()->popScene();
}




CCPoint Stage1::tileCoordForPosition(CCPoint position)
{
	int x = position.x / map->getTileSize().width;
	int y = ((map->getMapSize().height*map->getTileSize().height) - position.y) / map->getTileSize().height;

	return ccp(x, y);

}

bool Stage1::IsWall(CCPoint position)
{
	position -= Vec2(backgroundX, backgroundY);
	CCPoint tileCoord = tileCoordForPosition(position);

	if ((tileCoord.x < 0 || tileCoord.x >= mapSize.width) ||
		(tileCoord.y < 0 || tileCoord.y >= mapSize.height))
	{
		return false;
	}



	unsigned int tileGid = background1->tileGIDAt(tileCoord);
	unsigned int tileGid2 = background2->tileGIDAt(tileCoord);

	if (tileGid == 0 || tileGid2 != 0)
	{
		return false;

	}
	return true;


}

bool Stage1::checkChangeMap(CCPoint position)
{
	position -= Vec2(backgroundX, backgroundY);

	CCPoint tileCoord = tileCoordForPosition(position);

	if (tileCoord.x < 0 || tileCoord.x >= mapSize.width ||
		tileCoord.y < 0 || tileCoord.y >= mapSize.height)
	{
		return false;
	}

	if (background5 != nullptr)
	{
		unsigned int tileGid = background5->tileGIDAt(tileCoord);

		if (tileGid != 0)
		{
			return true;
		}
	}
	return false;
}

void Stage1::changeMap(void)
{

	removeChild(map);
	map = CCTMXTiledMap::create("blackforest.tmx");
	mapSize = map->getMapSize();
	character->setPosition(winSize.width - character->getPositionX(), character->getPositionY());
	backgroundX = 0;
	backgroundY = 0;
	background1 = map->layerNamed(TEMP_DEFINE::TILELAYER_1);
	background2 = map->layerNamed(TEMP_DEFINE::TILELAYER_2);
	background3 = map->layerNamed(TEMP_DEFINE::TILELAYER_3);
	background4 = map->layerNamed(TEMP_DEFINE::TILELAYER_4);
	background5 = nullptr;

	addChild(map, 1);
}

Vec2 Stage1::setCharacterPosition(Vec2 position, Vec2 moveVec)
{
	bool backMoveX = false;
	bool backMoveY = false;

	if (moveVec.x < 0)
	{
		if (backgroundX < 0 && position.x <= winSize.width / 2)
		{
			backgroundX += TEMP_DEFINE::MAP_MOVE_SPEED;
			backMoveX = true;
		}
		else
		{
			if (backgroundX > 0)
			{
				backgroundX = 0;
			}
			moveVec.add(Vec2(-TEMP_DEFINE::TAG_MOVE_SPEED, 0));
			if (position.x - TEMP_DEFINE::TAG_MOVE_SPEED < 16)
			{
				moveVec.x = 0;
			}
		}

	}
	else if (moveVec.x > 0)
	{
		if (backgroundX > -(mapSize.width * 32 - winSize.width) && position.x >= winSize.width / 2)
		{
			backgroundX -= TEMP_DEFINE::MAP_MOVE_SPEED;
			backMoveX = true;
		}
		else
		{
			if (backgroundX <= -(mapSize.width * 32 - winSize.width))
			{
				backgroundX = -(mapSize.width * 32 - winSize.width);
			}
			moveVec.add(Vec2(TEMP_DEFINE::TAG_MOVE_SPEED, 0));
			if (position.x + TEMP_DEFINE::TAG_MOVE_SPEED >= winSize.width)
			{
				moveVec.x = 0;
			}
		}
	}

	if (moveVec.y < 0)
	{
		if (backgroundY < 0 && position.y <= winSize.height / 2)
		{
			backgroundY += TEMP_DEFINE::MAP_MOVE_SPEED;
			backMoveY = true;
		}
		else
		{
			if (backgroundY >= 0)
			{
				backgroundY = 0;
			}
			moveVec.add(Vec2(0, -TEMP_DEFINE::TAG_MOVE_SPEED));
			if (position.y - TEMP_DEFINE::TAG_MOVE_SPEED < 16)
			{
				moveVec.y = 0;
			}
		}
	}
	else if (moveVec.y > 0)
	{
		if (backgroundY > -(mapSize.height * 32 - winSize.height) && position.y >= winSize.height / 2)
		{
			backgroundY -= TEMP_DEFINE::MAP_MOVE_SPEED;
			backMoveY = true;
		}
		else
		{
			if (backgroundY <= -(mapSize.height * 32 - winSize.height))
			{
				backgroundY = -(mapSize.height * 32 - winSize.height);
			}
			moveVec.add(Vec2(0, TEMP_DEFINE::TAG_MOVE_SPEED));
			if (position.y + TEMP_DEFINE::TAG_MOVE_SPEED >= winSize.height)
			{
				moveVec.y = 0;
			}
		}
	}


	if (backMoveX && backMoveY)
	{
		return position;
	}
	return position + moveVec;
}

bool Stage1::backgroundMove()
{
	if ((backgroundX <= 0 && backgroundX >= -(mapSize.width * 32 - winSize.width)) ||
		(backgroundY <= 0 && backgroundY >= -(mapSize.height * 32 - winSize.height))
		)
	{
		return true;
	}
	return false;

}
bool Stage1::characterMove(Vec2 position)
{
	if (position.x != winSize.width / 2 ||
		position.y != winSize.height / 2)
	{
		return true;
	}
	return false;
}


Stage1::Stage1()
{
}

Stage1::~Stage1()
{
}
