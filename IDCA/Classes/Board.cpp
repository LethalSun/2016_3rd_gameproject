#include "pch.h"
#include "Board.h"
#include "PlayerCharacter.h"
#include "InputLayer.h"
#include "Define.h"
#include "EscMenu.h"
#include "PlayerMenu.h"


Board* Board::create(PlayerCharacter* player)
{
	auto self = new (std::nothrow) Board();

	if (self && self->init(player))
	{
		self->autorelease();
		return self;
	}
	else
	{
		delete(self);
		self = nullptr;
		return self;
	}

}

bool Board::init(PlayerCharacter* player)
{
	if (!Node::init())
	{
		return false;

	}



	m_pInputLayer = InputLayer::create();
	addChild(m_pInputLayer);

	m_pPlayerMenu = PlayerMenu::create(player);
	addChild(m_pPlayerMenu);

	scheduleUpdate();
	return true;
}


void Board::update(float deltaTime)
{
	m_inputArray = m_pInputLayer->GetInputArray();

	if ((m_inputArray[INPUT_LAYER::keyESC]) == INPUT_LAYER::START)
	{
		
		m_inputArray = m_pInputLayer->GetInputArray();

		m_pInputLayer->MemoryClear();

		Director::getInstance()->pushScene(m_pEscMenu->createScene());

	}


}

