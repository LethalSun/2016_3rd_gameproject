#include "pch.h"
#include "EscMenu.h"
#include "InputLayer.h"
#include "HelloWorldScene.h"




Scene* EscMenu::createScene()
{
	auto Scene = Scene::create();
	auto layer = EscMenu::create();

	Scene->addChild(layer);

	return Scene;
}


bool EscMenu::init()
{
	if (!Layer::init())
	{
		return false;
	}

	m_pInputLayer = InputLayer::create();
	addChild(m_pInputLayer);



	/// 메뉴를 넣어보자

	auto returnToMain = MenuItemFont::create("Return to Main", CC_CALLBACK_1(EscMenu::returnToMain, this));

	auto returnToGame = MenuItemFont::create("Return to Game", CC_CALLBACK_1(EscMenu::returnToGame, this));

	auto escMenu = Menu::create(returnToMain, returnToGame, NULL);

	escMenu->alignItemsVerticallyWithPadding(300.f);
	addChild(escMenu);

	scheduleUpdate();
	return true;



}

void EscMenu::update(float delta)
{
	

}

void EscMenu::returnToMain(cocos2d::Ref* pSender)
{

	auto mainscene = HelloWorld::createScene();
	Director::getInstance()->replaceScene(mainscene);

}

void EscMenu::returnToGame(cocos2d::Ref* pSender)
{
	Director::getInstance()->popScene();
}
