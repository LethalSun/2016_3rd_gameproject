#include "pch.h"
#include "DeadScene.h"
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "InputLayer.h"


// Cocos2d-x 기본 씬 생성 함수.
Scene* DeadScene::createScene()
{
	auto scene = Scene::create();

	auto layer = DeadScene::create();

	scene->addChild(layer);

	return scene;
}

// 씬 초기화 함수.
bool DeadScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	setIsCharacterAppeared(false);
	
	// GameOver Sound 등록.
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(DEAD_SCENE_LOST_SOUND, false);

	// GameOver Title 등록.
	auto title = Sprite::create(DEAD_SCENE_GAME_OVER_TITLE);
	title->setPosition(Vec2(0, visibleSize.height + title->getContentSize().height));
	addChild(title);

	// Title 액션 등록.
	auto bounceAction = JumpTo::create(DEAD_SCENE_BOUNCE_TIME, Vec2(visibleSize.width * DEAD_SCENE_TITLE_WIDTH, visibleSize.height * DEAD_SCENE_TITLE_HEIGHT), DEAD_SCENE_TITLE_JUMP_HEIGHT, DEAD_SCENE_TITLE_JUMP_NUMBER);
	auto easeBounceAction = EaseOut::create(bounceAction, DEAD_SCENE_TITLE_EASE_SPEED);
	title->runAction(easeBounceAction);

	scheduleUpdate();

	return true;
}

void DeadScene::update(float dt)
{
	m_AcculmulateTime += dt;
	
	if (!getIsCharacterAppeared() && (DEAD_SCENE_BOUNCE_TIME + DEAD_SCENE_REST_TIME < m_AcculmulateTime))
	{
		auto visibleSize = Director::getInstance()->getVisibleSize();

		// GameOver Sound 등록.
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(DEAD_SCENE_GAME_OVER_SOUND, false);
		
		// 캐릭터 등록.
		auto character = Sprite::create(DEAD_SCENE_CHARACTER_WITH_LIGHT);
		character->setOpacity(0);
		character->setPosition(Vec2(visibleSize.width * DEAD_SCENE_CHARACTER_WIDTH, visibleSize.height * DEAD_SCENE_CHARACTER_HEIGHT));
		addChild(character);

		// FadeIn 액션 등록.
		auto FadeInAction = FadeIn::create(DEAD_SCENE_FADE_IN_TIME);
		auto TextFunc = CallFunc::create(CC_CALLBACK_0(DeadScene::TextTwinkle, this));
		auto seqAction = Sequence::create(FadeInAction, TextFunc, nullptr);
		character->runAction(seqAction);

		// InputLayer 등록
		m_pInputLayer = InputLayer::create();
		addChild(m_pInputLayer);

		setIsCharacterAppeared(true);
	}

	// Character가 등장한 시점부터 입력을 받을 수 있다.
	if (getIsCharacterAppeared())
	{
		auto startChecker = m_pInputLayer->GetInputArray();

		if (startChecker[INPUT_LAYER::ARRAY_INDEX::keyAttack] == INPUT_LAYER::KEY_STATUS::END)
		{
			ChangeToHelloWorldScene();
		}
	}

	return;
}


void DeadScene::ChangeToHelloWorldScene()
{
	Director::getInstance()->replaceScene(HelloWorld::createScene());
	return;
}

void DeadScene::TextTwinkle()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();

	// 텍스트 등록.
	auto RestartText = Sprite::create(DEAD_SCENE_RESTART_TITLE);
	RestartText->setPosition(Vec2(visibleSize.width * DEAD_SCENE_TEXT_WIDTH, visibleSize.height * DEAD_SCENE_TEXT_HEIGHT));
	addChild(RestartText);

	// 텍스트 액션 등록.
	auto actionFadeOut = FadeOut::create(DEAD_SCENE_RESTART_TWINKLE_TIME);
	auto actionFadeIn = FadeIn::create(DEAD_SCENE_RESTART_TWINKLE_TIME);
	auto textSequence = Sequence::createWithTwoActions(actionFadeOut, actionFadeIn);
	auto repeatTextAction = RepeatForever::create(textSequence);
	RestartText->runAction(repeatTextAction);

	return;
}