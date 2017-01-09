#pragma once

class InputLayer : public Layer
{
public:
	CREATE_FUNC(InputLayer);

	/* Basic Functions */
	virtual bool			init();
	virtual void			update(const float);
	bool					MemoryClear();

	/* Get input Function */
	int*					GetInputArray();
	int*					GetInputUnitVec();


	/* JoyStick Input Setting & Functions */
	gainput::InputManager	m_Manager;
	gainput::InputMap	   *m_pMap;

	void					MapKeySetting(const unsigned int);
	void 					DetectJoyStickInput();
	void					ConvertJoyStickToUnitVec(const float, const float);
	void					CheckBoolIsNew(float*, float*);
	void					CheckBoolIsDown(float*, float*);
	void					MapRelease();

	/* Keyborad Input Setting & Functions */
	virtual void			onKeyPressed(EventKeyboard::KeyCode, Event*);
	virtual void			onKeyReleased(EventKeyboard::KeyCode, Event*);

private:
	/* Delivery Data Structure & Functions */
	int 					m_CurrentInputArray[INPUT_LAYER::ARRAY_INDEX::stateIdxNum];
	int 					m_OldInputArray[INPUT_LAYER::ARRAY_INDEX::stateIdxNum];
	int						m_CurrentInputUnitVec[INPUT_LAYER::UNIT_VEC_INDEX::vecIdxNum];
	int						m_OldInputUnitVec[INPUT_LAYER::UNIT_VEC_INDEX::vecIdxNum];
	
	int						m_InputUnitVec[INPUT_LAYER::UNIT_VEC_INDEX::vecIdxNum];
	int						m_InputArray[INPUT_LAYER::ARRAY_INDEX::stateIdxNum];
	int						m_ArrowContainer[INPUT_LAYER::ARROW::ARROW_NUM];

	void					DefineWhatIsUnitVec();
	void					DefineWhatIsInputValue();
	bool					IsJoyStickButtonPressed();
	bool					IsArrowContainerEmpty();
	void					InsertCurToOld();

	bool					m_IsKeyboardPressed;
};
