#include "pch.h"
#include "Player.h"


bool Player::init()
{
	if (!Sprite::init())
	{
		return false;
	}

	Point WIN_SIZE(1024.f, 768.f);
	Point POS_INIT(300.f, 300.f);

	// Sprite 세팅
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(PLAYER_PLIST);
	m_pCharacter = Sprite::createWithSpriteFrameName(PLAYER_SPRITE);
	m_pCharacter->setPosition(POS_INIT);
	
	addChild(m_pCharacter);
	
	 
	// JoyStick 세팅
	m_pMap = new InputMap(m_Manager);

	m_Manager.SetDisplaySize(WIN_SIZE.x, WIN_SIZE.y);
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
		auto x = m_pMap->GetFloat(LeftStickX);
		auto y = m_pMap->GetFloat(LeftStickY);
		auto move = MoveBy::create(0, Vec2(x * MOVE_SPEED * dt, y * MOVE_SPEED * dt));
		m_pCharacter->runAction(move);
	}
}