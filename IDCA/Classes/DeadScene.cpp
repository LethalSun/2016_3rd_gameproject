#include "pch.h"
#include "DeadScene.h"
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "InputLayer.h"

const char LostGameSound[] = "EndingScene/LostGame.wav";
const char GameOverSound[] = "EndingScene/GameOverSound.wav";

const float BounceTime = 3.0f;
const float RestTime = 0.3f;
const float FadeInTime = 1.f;

const char GameOverTitle[] = "EndingScene/GameOver.png";
const char CharacterWithLight[] = "EndingScene/CharacterWithLight.png";
const char TextImg[] = "EndingScene/Restart.png";
const float RestartTextTwinkleTime = 2.0f;

// Cocos2d-x �⺻ �� ���� �Լ�.
Scene* DeadScene::createScene()
{
	auto scene = Scene::create();

	auto layer = DeadScene::create();

	scene->addChild(layer);

	return scene;
}

// �� �ʱ�ȭ �Լ�.
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
	
	// GameOver Sound ���.
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(LostGameSound, false);

	// GameOver Title ���.
	auto title = Sprite::create(GameOverTitle);
	title->setPosition(Vec2(0, visibleSize.height + title->getContentSize().height));
	addChild(title);

	// Title �׼� ���.
	// TODO :: ���� �ѹ�.
	auto bounceAction = JumpTo::create(BounceTime, Vec2(visibleSize.width * 0.5f, visibleSize.height * 0.6f), 150, 7);
	auto easeBounceAction = EaseOut::create(bounceAction, 3.0);
	title->runAction(easeBounceAction);

	// InputLayer ���
	m_pInputLayer = InputLayer::create();
	addChild(m_pInputLayer);

	scheduleUpdate();

	return true;
}

void DeadScene::update(float dt)
{
	m_AcculmulateTime += dt;
	
	if (!getIsCharacterAppeared() && (BounceTime + RestTime < m_AcculmulateTime))
	{
		auto visibleSize = Director::getInstance()->getVisibleSize();

		// GameOver Sound ���.
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(GameOverSound, false);
		
		// ĳ���� ���.
		auto character = Sprite::create(CharacterWithLight);
		character->setOpacity(0);
		character->setPosition(Vec2(visibleSize.width * 0.5f, visibleSize.height * 0.4f));
		addChild(character);

		// FadeIn �׼� ���.
		auto FadeInAction = FadeIn::create(FadeInTime);
		auto TextFunc = CallFunc::create(CC_CALLBACK_0(DeadScene::TextTwinkle, this));
		auto seqAction = Sequence::create(FadeInAction, TextFunc, nullptr);
		character->runAction(seqAction);

		setIsCharacterAppeared(true);
	}

	auto startChecker = m_pInputLayer->GetInputArray();

	if (startChecker[INPUT_LAYER::ARRAY_INDEX::keyAttack] == INPUT_LAYER::KEY_STATUS::END)
	{
		ChangeToHelloWorldScene();
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

	// �ؽ�Ʈ ���.
	auto RestartText = Sprite::create(TextImg);
	RestartText->setPosition(Vec2(visibleSize.width * 0.5f, visibleSize.height * 0.2f));
	addChild(RestartText);

	// �ؽ�Ʈ �׼� ���.
	auto actionFadeOut = FadeOut::create(RestartTextTwinkleTime);
	auto actionFadeIn = FadeIn::create(RestartTextTwinkleTime);
	auto textSequence = Sequence::createWithTwoActions(actionFadeOut, actionFadeIn);
	auto repeatTextAction = RepeatForever::create(textSequence);
	RestartText->runAction(repeatTextAction);
	return;
}