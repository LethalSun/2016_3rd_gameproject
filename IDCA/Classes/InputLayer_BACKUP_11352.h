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
		unitVecXStatus = 0, unitVecYStatus = 1,

		// Keyborad Input idx
		keyQ = 2, keyW = 3, keyE = 4, keyESC = 5,

		// JoyStick Input idx

		joyA = 6, joyB = 7, joyX = 8, joyStart = 9,
		stateIdxNum = 10
	};

	enum UNIT_VEC_INDEX
	{
		unitVecX = 0, unitVecY = 1,
		vecIdxNum = 2
	};

	// Key의 상태를 나타내줄 ENUM 값.
	enum KEY_STATUS
	{
		NONE = 0, START = 1, HOLD = 2, END = 3
	};

	/* Basic Functions */
	virtual bool			init();
	virtual void			update(const float);

<<<<<<< HEAD

	/* Delivery Data Structure & Functions */
	int 					m_CurrentInputArray[idxNum];
	int 					m_OldInputArray[idxNum];
	
	int						m_InputArray[idxNum];
	
	void					DefineWhatIsInputValue();
	
=======
	/* Get input Function */
	int*					GetInputArray();
	int*					GetInputUnitVec();
>>>>>>> 5a97256713f668309aefa7f7c33f55558af59826

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
	virtual void			onKeyPressed(EventKeyboard::KeyCode, Event*);
	virtual void			onKeyReleased(EventKeyboard::KeyCode, Event*);

private:
	// TODO :: Array 두 가지로 나눠보기 (UnitVec, Status);
	// TODO :: Public 변수로 만들어서 차라리 Get함수를 지원해주자.
	/* Delivery Data Structure & Functions */
	int 					m_CurrentInputArray[stateIdxNum];
	int 					m_OldInputArray[stateIdxNum];

	int				m_InputUnitVec[vecIdxNum];
	int				m_InputArray[stateIdxNum];

	void					DefineWhatIsInputValue();
};
