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

	// TODO :: override�� �� �Ÿ� �� ����, �� ���Ÿ� �� �Ⱦ�����. �ϰ��� �ְ� �ٲٱ�.
	/* Keyborad Input Setting & Functions */
	virtual void			onKeyPressed(EventKeyboard::KeyCode, Event*);
	virtual void			onKeyReleased(EventKeyboard::KeyCode , Event*);

private :
	// TODO :: Array �� ������ �������� (UnitVec, Status);
	// TODO :: Public ������ ���� ���� Get�Լ��� ����������.
	/* Delivery Data Structure & Functions */
	int 					m_CurrentInputArray[INPUT_LAYER::ARRAY_INDEX::stateIdxNum];
	int 					m_OldInputArray[INPUT_LAYER::ARRAY_INDEX::stateIdxNum];
	
	static int				m_InputUnitVec[INPUT_LAYER::UNIT_VEC_INDEX::vecIdxNum];
	static int				m_InputArray[INPUT_LAYER::ARRAY_INDEX::stateIdxNum];
	
	void					DefineWhatIsInputValue();
};

