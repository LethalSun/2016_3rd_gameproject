#include "pch.h"
#include "EndingScene.h"
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "InputLayer.h"



// Cocos2d-x �⺻ �� ���� �Լ�.
Scene* EndingScene::createScene()
{
	auto scene = Scene::create();

	auto layer = EndingScene::create();

	scene->addChild(layer);

	return scene;
}

// �� �ʱ�ȭ �Լ�.
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

	// Victory Sound ���.
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(ENDING_SCENE_HOORAY_SOUND, false);
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(ENDING_SCENE_BGM, false);

	// Victory Title ���.
	auto title = Sprite::create(ENDING_SCENE_VICTIORY_TITLE);
	title->setPosition(Vec2(visibleSize.width * ENDING_SCENE_TITLE_WIDTH, -title->getContentSize().height));
	addChild(title);

	// Title �׼� ���.
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

		// Victory Sound ���.
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(ENDING_SCENE_YEAH_SOUND, false);

		TextTwinkle();

		// InputLayer ���
		m_pInputLayer = InputLayer::create();
		addChild(m_pInputLayer);

		setIsVictoryAppeared(true);
	}

	// ����ŸƮ �ؽ�Ʈ�� ���� ���Ŀ����� �Է��� ���� �� �ֵ��� ó��.
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

	// �ؽ�Ʈ ���.
	auto RestartText = Sprite::create(ENDING_SCENE_RESTART_TEXT);
	RestartText->setPosition(Vec2(visibleSize.width * ENDING_SCENE_TEXT_WIDTH, visibleSize.height * ENDING_SCENE_TEXT_HEIGHT));
	addChild(RestartText);

	// �ؽ�Ʈ �׼� ���.
	auto actionFadeOut = FadeOut::create(ENDING_SCENE_RESTART_TWINKLE_TIME);
	auto actionFadeIn = FadeIn::create(ENDING_SCENE_RESTART_TWINKLE_TIME);
	auto textSequence = Sequence::createWithTwoActions(actionFadeOut, actionFadeIn);
	auto repeatTextAction = RepeatForever::create(textSequence);
	RestartText->runAction(repeatTextAction);
	return;
}