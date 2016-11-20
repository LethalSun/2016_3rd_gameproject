#include "pch.h"
#include "Player.h"


bool Player::init()
{
	if (!Sprite::init())
	{
		return false;
	}

	// Sprite 세팅
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Walking.plist");
	m_pCharacter = Sprite::createWithSpriteFrameName("WalkingFront01.png");
	m_pCharacter->setPosition(Point(300, 300));
	
	addChild(m_pCharacter);
	
	 
	// JoyStick 세팅
	m_pMap = new InputMap(m_Manager);

	m_Manager.SetDisplaySize(1024, 768);
	const gainput::DeviceId padId = m_Manager.CreateDevice<gainput::InputDevicePad>();
	MapKeySetting(padId);

	scheduleUpdate();
	return true;
}


void Player::MapKeySetting(const unsigned int padId)
{
	m_pMap->MapFloat(LeftStickX, padId, PadButtonLeftStickX);
	m_pMap->MapFloat(LeftStickY, padId, PadButtonLeftStickY);
}


void Player::StickMove(float dt)
{
	if (m_pMap->GetBool(LeftStickX) || m_pMap->GetBool(LeftStickY))
	{
		float x = m_pMap->GetFloat(LeftStickX);
		float y = m_pMap->GetFloat(LeftStickY);
		auto move = MoveBy::create(0, Vec2(x * MOVE_SPEED * dt, y * MOVE_SPEED * dt));
		m_pCharacter->runAction(move);
	}
}