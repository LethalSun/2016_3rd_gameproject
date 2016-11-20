#pragma once

using namespace gainput;

// Gainput ���̺귯�� ������ �˾ƺ��� ���Ͽ� ������ �ӽ� Player Ŭ����.
// ��ƽ �Է��� �޾� �����δ�.
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

