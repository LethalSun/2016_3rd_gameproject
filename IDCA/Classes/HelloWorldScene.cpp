#include "pch.h"
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "StageOne.h"
#include "InputLayer.h"

const char BGM[] = "TitleScene/Bgm.mp3";

const char BackgroundImg[] = "TitleScene/Background.png";
const float BackgroundWidth = 0.5f;
const float BackgroundHeight = 0.5f;

const char TitleImg[] = "TitleScene/Title.png";
const float TitleWidth = 0.5f;
const float TitleHeight = 0.75;

const char ButtonStartNormal[] = "TitleScene/Play_Normal.png";
const char ButtonStartSelected[] = "TitleScene/Play_Selected.png";
const char ButtonExitNormal[] = "TitleScene/Exit_Normal.png";
const char ButtonExitSelected[] = "TitleScene/Exit_Normal.png";

const float MenuWidth = 0.3f;
const float MenuHeight = 0.4f;

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
	auto Background = Sprite::create(BackgroundImg);
	Background->setPosition(Vec2(visibleSize.width * BackgroundWidth, visibleSize.height * BackgroundHeight));
	addChild(Background);

	// 타이틀 등록.
	auto Title = Sprite::create(TitleImg);
	Title->setPosition(Vec2(visibleSize.width * TitleWidth, visibleSize.height * TitleHeight));
	addChild(Title);

	// 배경음 등록.
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(BGM, true);
	
	// InputLayer 등록.
	m_pInputLayer = InputLayer::create();
	addChild(m_pInputLayer);

	scheduleUpdate();

	return true;
}

void HelloWorld::update(float dt)
{
	// TODO :: Press Q to Start, ESC to exit로 바꿔주기. 
	auto startChecker = m_pInputLayer->GetInputArray();
	
	char buf[255];
	sprintf(buf, "keyAttack : %d", startChecker[INPUT_LAYER::ARRAY_INDEX::keyAttack]);
	CCLOG(buf);


	if (startChecker[INPUT_LAYER::ARRAY_INDEX::keyAttack] == INPUT_LAYER::KEY_STATUS::END)
	{
		ChangeToStageOne();
	}
	else if (startChecker[INPUT_LAYER::ARRAY_INDEX::keyESC] == INPUT_LAYER::KEY_STATUS::END)
	{
		ExitGame();
	}
}

void HelloWorld::ChangeToStageOne()
{
	Director::getInstance()->replaceScene(StageOne::createScene());
}

void HelloWorld::ExitGame()
{
	exit(0);
}