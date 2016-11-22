#include "pch.h"
#include "KeyboardLayer.h"
#include "CharacterManager.h"

Scene* KeyboardLayer::createScene()
{
	auto scene = Scene::create();

	KeyboardLayer* layer = KeyboardLayer::create();
	scene->addChild(layer);
	return scene;
}

bool KeyboardLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	m_keyboardInput = 0;

	characterManager = CharacterManager::create();
	this->addChild(characterManager);
	auto eventListener = EventListenerKeyboard::create();

	eventListener->onKeyPressed = CC_CALLBACK_2(KeyboardLayer::onKeyPressed, this);
	eventListener->onKeyReleased = CC_CALLBACK_2(KeyboardLayer::onKeyReleased, this);

	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, this);

	this->scheduleUpdate();
	return true;
}

void KeyboardLayer::onKeyPressed(EventKeyboard::KeyCode keyCode, Event * event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW)
	{
		m_keyboardInput |= KEY_BOARD_INPUT::UP;
	}

	else if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW)
	{
		m_keyboardInput |= KEY_BOARD_INPUT::DOWN;
	}

	else if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
	{
		m_keyboardInput |= KEY_BOARD_INPUT::RIGHT;
	}

	else if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
	{
		m_keyboardInput |= KEY_BOARD_INPUT::LEFT;
	}

	else if (keyCode == EventKeyboard::KeyCode::KEY_A)
	{
		m_keyboardInput |= KEY_BOARD_INPUT::A;
	}
}

void KeyboardLayer::onKeyReleased(EventKeyboard::KeyCode keyCode, Event * event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW)
	{
		m_keyboardInput &= ~(KEY_BOARD_INPUT::UP);
	}

	else if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW)
	{
		m_keyboardInput &= ~(KEY_BOARD_INPUT::DOWN);
	}

	else if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
	{
		m_keyboardInput &= ~(KEY_BOARD_INPUT::RIGHT);
	}

	else if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
	{
		m_keyboardInput &= ~(KEY_BOARD_INPUT::LEFT);
	}

	else if (keyCode == EventKeyboard::KeyCode::KEY_A)
	{
		m_keyboardInput &= ~(KEY_BOARD_INPUT::A);
	}
}

const unsigned int  KeyboardLayer::GetKeyboardInput()
{
	// TODO: insert return statement here
	return m_keyboardInput;
}

void KeyboardLayer::update(float delta)
{
	//characterManager->SetKeyboardInput(GetKeyboardInput());
	characterManager->update(delta);
}