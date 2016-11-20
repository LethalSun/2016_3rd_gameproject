#pragma once

using namespace gainput;

class Player : public Sprite
{
public:
	CREATE_FUNC(Player);

	virtual bool			init();


	/* JoyStick Setting */
	void					MapKeySetting(const unsigned int);
	void					StickMove();
	InputManager			m_Manager;
	InputMap			   *m_pMap;


	/* Animation */
	SpriteFrameCache	   *m_pFrame;
	Animation			   *m_pAnimation;
	Animate				   *m_pAnimate;


	/* Member Variables */
	Sprite				   *m_pCharacter;

	

};

