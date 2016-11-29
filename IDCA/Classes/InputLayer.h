#pragma once

class InputLayer : public Layer
{
public:
	CREATE_FUNC(InputLayer);

	/* const & enum values */
	enum ARRAY_INDEX
	{

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


	// JoyStick Mapping을 위한 값.
	const int JoyStickX = 0;
	const int JoyStickY = 1;


	/* Basic Functions */
	virtual bool			init();
	virtual void			update(const float);


	/* Delivery Data Structure & Functions */
	int 					m_CurrentInputArray[idxNum];
	int 					m_OldInputArray[idxNum];
	
	int						m_InputArray[idxNum];
	
	void					DefineWhatIsInputValue();
	

	/* JoyStick Input Setting & Functions */
	gainput::InputManager	m_Manager;
	gainput::InputMap	   *m_pMap;

	void					MapKeySetting(const unsigned int);
	void					DetectJoyStickInput();
	void					ConvertJoyStickToUnitVec(const float, const float);
	void					CheckBoolIsNew();
	void					CheckBoolIsDown();


	/* Keyborad Input Setting & Functions */
	virtual void			onKeyPressed(EventKeyboard::KeyCode, Event*) override;
	virtual void			onKeyReleased(EventKeyboard::KeyCode , Event*) override;

};

