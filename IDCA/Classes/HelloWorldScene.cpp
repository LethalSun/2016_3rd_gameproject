#include "pch.h"
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "StageOne.h"
#include "InputLayer.h"

const char BGM[] = "TitleScene/Bgm.mp3";

const char BackgroundImg[] = "TitleScene/Background.png";
const float BackgroundWidth = 0.5f;
const float BackgroundHeight = 0.5f;

const char TitleImg[] = "TitleScene/Title_darker.png";
const float TitleWidth = 0.5f;
const float TitleHeight = 0.75f;

const char TextBackgroundImg[] = "TitleScene/TitleTextBackground_softsmall.png";
const float TextBackgroundWidth = 0.5f;
const float TextBackgroundHeight = 0.2f;

const char SelectTextKeyboard[] = "TitleScene/TitleTextKeyboard_agencysmall.png";

const float SelectTextTwinkleTime = 1.0f;

// Cocos2d-x 기본 씬 생성 함수.
Scene* HelloWorld::createScene()
{
	auto scene = Scene::create();

	auto layer = HelloWorld::create();

	scene->addChild(layer);

	return scene;
}

// 씬 초기화 함수.
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

	// 텍스트 백그라운드 등록.
	auto TextBackground = Sprite::create(TextBackgroundImg);
	TextBackground->setPosition(Vec2(visibleSize.width * TextBackgroundWidth, visibleSize.height * TextBackgroundHeight));
	addChild(TextBackground);

	// 텍스트 등록.
	auto SelectText = Sprite::create(SelectTextKeyboard);
	SelectText->setPosition(Vec2(visibleSize.width * TextBackgroundWidth, visibleSize.height * TextBackgroundHeight - 7.5f));
	addChild(SelectText);

	// 텍스트 액션 등록.
	auto actionFadeOut = FadeOut::create(SelectTextTwinkleTime);
	auto actionFadeIn = FadeIn::create(SelectTextTwinkleTime);
	auto textSequence = Sequence::createWithTwoActions(actionFadeOut, actionFadeIn);
	auto repeatTextAction = RepeatForever::create(textSequence);
	SelectText->runAction(repeatTextAction);

	// 배경음 등록.
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(BGM, true);
	
	// InputLayer 등록.
	m_pInputLayer = InputLayer::create();
	addChild(m_pInputLayer);

	scheduleUpdate();

	return true;
}

// 키가 눌렸는지 체크해주고 프로그램을 종료하거나 StageOne으로 이동.
void HelloWorld::update(float dt)
{
	auto startChecker = m_pInputLayer->GetInputArray();
	
	if (startChecker[INPUT_LAYER::ARRAY_INDEX::keyAttack] == INPUT_LAYER::KEY_STATUS::END)
	{
		ChangeToStageOne();
	}
	else if (startChecker[INPUT_LAYER::ARRAY_INDEX::keyESC] == INPUT_LAYER::KEY_STATUS::END)
	{
		ExitGame();
	}

	return;
}

// StageOne으로 이동. replaceScene 사용. (다시 돌아올 일이 없으므로)
void HelloWorld::ChangeToStageOne()
{
	m_pInputLayer->MapRelease();
	Director::getInstance()->replaceScene(StageOne::createScene());
	return;
}

// 프로그램 종료.
void HelloWorld::ExitGame()
{
	m_pInputLayer->MapRelease();
	exit(0);
	return;
}