#pragma once

using namespace gainput;

// Gainput 라이브러리 동작을 알아보기 위하여 생성한 임시 Player 클래스.
// 스틱 입력을 받아 움직인다.
class Player : public Sprite
{
public:
	CREATE_FUNC(Player);

	virtual bool			init();


	/* JoyStick Setting */
	void					MapKeySetting(const unsigned int);
	void					StickMove(float dt);
	InputManager			m_Manager;
	InputMap			   *m_pMap;


	/* Animation */
	SpriteFrameCache	   *m_pFrame;
	Animation			   *m_pAnimation;
	Animate				   *m_pAnimate;


	/* Member Variables */
	Sprite				   *m_pCharacter;

	

};

