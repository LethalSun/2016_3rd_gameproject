#include "pch.h"
#include "EndingScene.h"
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "InputLayer.h"

const char HooraySound[] = "EndingScene/Hooray.wav";
const char EndingBGM[] = "EndingScene/EndingBGM.wav";
const char YeahSound[] = "EndingScene/Yeah.wav";

const float RaiseTime = 1.5f; 
const float RestTime = 0.3f;
const float FadeInTime = 1.f;

const char VictoryTitle[] = "EndingScene/Victory.png";

const char TextImg[] = "EndingScene/Restart.png";
const float RestartTextTwinkleTime = 2.0f;

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
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(HooraySound, false);
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(EndingBGM, false);

	// Victory Title 등록.
	auto title = Sprite::create(VictoryTitle);
	title->setPosition(Vec2(visibleSize.width * 0.5f, -title->getContentSize().height));
	addChild(title);

	// Title 액션 등록.
	// TODO :: 매직 넘버.
	auto raiseAction = MoveTo::create(RaiseTime, Vec2(visibleSize.width * 0.5f, visibleSize.height * 0.6f));
	auto easeRaiseAction = EaseOut::create(raiseAction, 3.0);
	title->runAction(easeRaiseAction);

	// InputLayer 등록
	m_pInputLayer = InputLayer::create();
	addChild(m_pInputLayer);

	scheduleUpdate();

	return true;
}

void EndingScene::update(float dt)
{
	m_AcculmulateTime += dt;

	if (!getIsVictoryAppeared() && (RaiseTime + RestTime < m_AcculmulateTime))
	{
		auto visibleSize = Director::getInstance()->getVisibleSize();

		// Victory Sound 등록.
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(YeahSound, false);

		TextTwinkle();


		setIsVictoryAppeared(true);
	}

	auto startChecker = m_pInputLayer->GetInputArray();

	if (startChecker[INPUT_LAYER::ARRAY_INDEX::keyAttack] == INPUT_LAYER::KEY_STATUS::END)
	{
		ChangeToHelloWorldScene();
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
	auto RestartText = Sprite::create(TextImg);
	RestartText->setPosition(Vec2(visibleSize.width * 0.5f, visibleSize.height * 0.2f));
	addChild(RestartText);

	// 텍스트 액션 등록.
	auto actionFadeOut = FadeOut::create(RestartTextTwinkleTime);
	auto actionFadeIn = FadeIn::create(RestartTextTwinkleTime);
	auto textSequence = Sequence::createWithTwoActions(actionFadeOut, actionFadeIn);
	auto repeatTextAction = RepeatForever::create(textSequence);
	RestartText->runAction(repeatTextAction);
	return;
}