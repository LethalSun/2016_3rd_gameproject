#pragma once

class InputLayer : public Layer
{
public:
	CREATE_FUNC(InputLayer);

	/* const & enum values */
	enum ARRAY_INDEX
	{
		// TODO :: ENUM값 명시적으로 표현 (unitVecX = 0, unitVecY = 1) 이런식으로.
		// ENUM은 하나로 빼서 한 곳에 모아 놓기. 헤더는 최대한 심플하게.
		// UnitVec은 키보드와 조이스틱 공용으로 관리 (-1, 0, 1)
		unitVecX, unitVecY,
		unitVecXStatus, unitVecYStatus,

		// Keyborad Input idx
		keyQ, keyW, keyE, keyESC,

		// JoyStick Input idx
		joyA, joyB, joyX, joyStart, 
		idxNum

	};

	// Key의 상태를 나타내줄 ENUM 값.
	enum KEY_STATUS
	{
		NONE, START, HOLD, END
	};

	// TODO :: 다른 애들이 볼 필요 없으면 cpp로 가야한다. cpp의 맨 위로 넣자.
	// JoyStick Mapping을 위한 값.
	const int JoyStickX = 0;
	const int JoyStickY = 1;


	/* Basic Functions */
	virtual bool			init();
	virtual void			update(const float);


	// TODO :: Array 두 가지로 나눠보기 (UnitVec, Status);
	// TODO :: Public 변수로 만들어서 차라리 Get함수를 지원해주자.
	/* Delivery Data Structure & Functions */
	int 					m_CurrentInputArray[idxNum];
	int 					m_OldInputArray[idxNum];
	
	static int				m_InputArray[idxNum];
	
	void					DefineWhatIsInputValue();
	

	/* JoyStick Input Setting & Functions */
	gainput::InputManager	m_Manager;
	gainput::InputMap	   *m_pMap;

	void					MapKeySetting(const unsigned int);
	void					DetectJoyStickInput();
	void					ConvertJoyStickToUnitVec(const float, const float);
	void					CheckBoolIsNew();
	void					CheckBoolIsDown();

	// TODO :: override를 쓸 거면 다 쓰고, 안 쓸거면 다 안쓰던지. 일관성 있게 바꾸기.
	/* Keyborad Input Setting & Functions */
	virtual void			onKeyPressed(EventKeyboard::KeyCode, Event*) override;
	virtual void			onKeyReleased(EventKeyboard::KeyCode , Event*) override;

};

