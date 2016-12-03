#pragma once

class InputLayer : public Layer
{
public:
	CREATE_FUNC(InputLayer);

	/* const & enum values */
	enum ARRAY_INDEX
	{
		// TODO :: ENUM�� ��������� ǥ�� (unitVecX = 0, unitVecY = 1) �̷�������.
		// ENUM�� �ϳ��� ���� �� ���� ��� ����. ����� �ִ��� �����ϰ�.
		// UnitVec�� Ű����� ���̽�ƽ �������� ���� (-1, 0, 1)
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

	// Key�� ���¸� ��Ÿ���� ENUM ��.
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

	// TODO :: override�� �� �Ÿ� �� ����, �� ���Ÿ� �� �Ⱦ�����. �ϰ��� �ְ� �ٲٱ�.
	/* Keyborad Input Setting & Functions */
	virtual void			onKeyPressed(EventKeyboard::KeyCode, Event*);
	virtual void			onKeyReleased(EventKeyboard::KeyCode, Event*);

private:
	// TODO :: Array �� ������ �������� (UnitVec, Status);
	// TODO :: Public ������ ���� ���� Get�Լ��� ����������.
	/* Delivery Data Structure & Functions */
	int 					m_CurrentInputArray[stateIdxNum];
	int 					m_OldInputArray[stateIdxNum];

	int				m_InputUnitVec[vecIdxNum];
	int				m_InputArray[stateIdxNum];

	void					DefineWhatIsInputValue();
};
