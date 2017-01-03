#include "pch.h"
#include "EndingScene.h"
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "InputLayer.h"



// Cocos2d-x 기본 씬 생성 함수.
Scene* EndingScene::createScene()
{
	auto scene = Scene::create();

	auto layer = EndingScene::create();

	scene->addChild(layer);

	return scene;
}

// 씬 초기화 함수.
bool EndingScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	setIsVictoryAppeared(false);

	// Victory Sound 등록.
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(ENDING_SCENE_HOORAY_SOUND, false);
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(ENDING_SCENE_BGM, false);

	// Victory Title 등록.
	auto title = Sprite::create(ENDING_SCENE_VICTIORY_TITLE);
	title->setPosition(Vec2(visibleSize.width * ENDING_SCENE_TITLE_WIDTH, -title->getContentSize().height));
	addChild(title);

	// Title 액션 등록.
	auto raiseAction = MoveTo::create(ENDING_SCENE_RASIE_TIME, Vec2(visibleSize.width * ENDING_SCENE_TITLE_WIDTH, visibleSize.height * ENDING_SCENE_TITLE_HEIGHT));
	auto easeRaiseAction = EaseOut::create(raiseAction, ENDING_SCENE_EASE_RATE);
	title->runAction(easeRaiseAction);


	scheduleUpdate();

	return true;
}

void EndingScene::update(float dt)
{
	m_AcculmulateTime += dt;

	if (!getIsVictoryAppeared() && (ENDING_SCENE_RASIE_TIME + ENDING_SCENE_REST_TIME < m_AcculmulateTime))
	{
		auto visibleSize = Director::getInstance()->getVisibleSize();

		// Victory Sound 등록.
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(ENDING_SCENE_YEAH_SOUND, false);

		TextTwinkle();

		// InputLayer 등록
		m_pInputLayer = InputLayer::create();
		addChild(m_pInputLayer);

		setIsVictoryAppeared(true);
	}

	// 리스타트 텍스트가 빛난 이후에서야 입력을 받을 수 있도록 처리.
	if (getIsVictoryAppeared())
	{
		auto startChecker = m_pInputLayer->GetInputArray();

		if (startChecker[INPUT_LAYER::ARRAY_INDEX::keyAttack] == INPUT_LAYER::KEY_STATUS::END)
		{
			ChangeToHelloWorldScene();
		}
	}

	return;
}


void EndingScene::ChangeToHelloWorldScene()
{
	Director::getInstance()->replaceScene(HelloWorld::createScene());
	return;
}

void EndingScene::TextTwinkle()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();

	// 텍스트 등록.
	auto RestartText = Sprite::create(ENDING_SCENE_RESTART_TEXT);
	RestartText->setPosition(Vec2(visibleSize.width * ENDING_SCENE_TEXT_WIDTH, visibleSize.height * ENDING_SCENE_TEXT_HEIGHT));
	addChild(RestartText);

	// 텍스트 액션 등록.
	auto actionFadeOut = FadeOut::create(ENDING_SCENE_RESTART_TWINKLE_TIME);
	auto actionFadeIn = FadeIn::create(ENDING_SCENE_RESTART_TWINKLE_TIME);
	auto textSequence = Sequence::createWithTwoActions(actionFadeOut, actionFadeIn);
	auto repeatTextAction = RepeatForever::create(textSequence);
	RestartText->runAction(repeatTextAction);
	return;
}