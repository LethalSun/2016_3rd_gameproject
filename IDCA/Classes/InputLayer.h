#pragma once

class InputLayer : public Layer
{
public:
	CREATE_FUNC(InputLayer);


	/* Basic Functions */
	virtual bool			init();
	virtual void			update(const float);

	
	/* Get input Function */
	int*					GetInputArray();
	int*					GetInputUnitVec();
	

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
	virtual void			onKeyReleased(EventKeyboard::KeyCode , Event*);

private :
	// TODO :: Array 두 가지로 나눠보기 (UnitVec, Status);
	// TODO :: Public 변수로 만들어서 차라리 Get함수를 지원해주자.
	/* Delivery Data Structure & Functions */
	int 					m_CurrentInputArray[INPUT_LAYER::ARRAY_INDEX::stateIdxNum];
	int 					m_OldInputArray[INPUT_LAYER::ARRAY_INDEX::stateIdxNum];
	
	static int				m_InputUnitVec[INPUT_LAYER::UNIT_VEC_INDEX::vecIdxNum];
	static int				m_InputArray[INPUT_LAYER::ARRAY_INDEX::stateIdxNum];
	
	void					DefineWhatIsInputValue();
};

