#include "pch.h"
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "StageOne.h"
#include "InputLayer.h"

const char BGM[] = "TitleScene/Bgm.mp3";

Scene* HelloWorld::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = HelloWorld::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool HelloWorld::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// 백그라운드 이미지 등록.
	auto Background = Sprite::create("TitleScene/Background.png");
	Background->setPosition(Vec2(visibleSize.width * 0.5f, visibleSize.height * 0.5f));
	addChild(Background);

	// 타이틀 등록.
	auto Title = Sprite::create("TitleScene/Title.png");
	Title->setPosition(Vec2(visibleSize.width * 0.5f, visibleSize.height * 0.75f));
	addChild(Title);

	// 배경음 등록.
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(BGM);
	
	// 버튼, 메뉴 등록
	auto itemStart = MenuItemImage::create("TitleScene/Play_Normal.png", "TitleScene/Play_Selected.png", CC_CALLBACK_1(HelloWorld::ChangeToStageOne, this));
	auto itemExit = MenuItemImage::create("TitleScene/Exit_Normal.png", "TitleScene/Exit_Selected.png", CC_CALLBACK_1(HelloWorld::ExitGame, this));

	auto menu = Menu::create(itemStart, itemExit, NULL);
	menu->alignItemsVertically();
	menu->setPosition(Vec2(visibleSize.width * 0.3f, visibleSize.height * 0.4f));
	this->addChild(menu);

	// InputLayer 등록.
	m_pInputLayer = InputLayer::create();

	// TODO :: Press Q to Start, ESC to exit로 바꿔주기. 


	scheduleUpdate();

	return true;
}

void HelloWorld::update(float dt)
{
}

void HelloWorld::ChangeToStageOne(Ref* pSender)
{
	Director::getInstance()->replaceScene(StageOne::createScene());
}

void HelloWorld::ExitGame(Ref* pSender)
{
	exit(0);
}