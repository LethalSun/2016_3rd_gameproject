#include "pch.h"
#include "InputLayer.h"

bool InputLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Vec2 WIN_SIZE(1024, 768);
	

	// Array ����.
	for (int i = unitVecX; i < idxNum; ++i)
	{
		m_CurrentInputArray[i] = NONE;
		m_OldInputArray[i] = NONE;
		m_InputArray[i] = NONE;
	}

	// JoyStick ����
	m_pMap = new gainput::InputMap(m_Manager);

	m_Manager.SetDisplaySize(WIN_SIZE.x, WIN_SIZE.y);
	const gainput::DeviceId padId = m_Manager.CreateDevice<gainput::InputDevicePad>();
	MapKeySetting(padId);


	// Keyboard ��ǲ�� ���� Listener ����.
	auto eventListener = EventListenerKeyboard::create();

	eventListener->onKeyPressed = CC_CALLBACK_2(InputLayer::onKeyPressed, this);
	eventListener->onKeyReleased = CC_CALLBACK_2(InputLayer::onKeyReleased, this);
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, this);

	scheduleUpdate();

	return true;
}


/*
	Update
	CurrentInputArray/OldInputArray�� ���Ͽ�
		JoyStick ��ǲ�� ����. ���� ����.
		Keyboard ��ǲ�� ����. ���� ����. (�����ʰ� �ڵ����� ����)

	����� ���� �������� InputArray�� ���� ����.
*/

void InputLayer::update(const float deltaTime)
{
	DetectJoyStickInput();
	DefineWhatIsInputValue();
}


/*
	DefineWhatIsInputValue
	CurrentInputArray�� OldInputArray�� ���Ͽ� InputValue�� ä���־��ִ� �Լ�.
	�⺻���� �Ǻ� �˰�����
	UnitVec�� ���ؼ� :
		Current���� �������.

	UnitVecStatus�� ���ؼ� :		
		UnitVecX, Y ������ ���Ͽ�,
		old(0) -> cur(0) : NONE
		old(0) -> cur(-1, 1) : START
		old(-1, 1) -> cur(0) : END
		old(-1 / 1) -> cur(-1 / 1) : HOLD (���� ������ ���)
		old(-1 / 1) -> cur(1 / -1) : START (�ٸ� ������ ���)

	Key�� ���ؼ� :
		Cur(END)�� ��� : END
		Cur(START)�� ��� : START
		Cur(NONE)�� ���
			Old(START) -> HOLD

		else ���� : NONE
*/

void InputLayer::DefineWhatIsInputValue()
{
	// UnitVec ó��
	for (int i = unitVecX; i <= unitVecY; ++i)
	{
		m_InputArray[i] = m_CurrentInputArray[i];
	}

	// UnitVecStatus ó��
	for (int i = unitVecXStatus; i <= unitVecYStatus; ++i)
	{
		if (m_OldInputArray[i] == 0)
		{
			if (m_CurrentInputArray[i] == 0)
			{
				m_InputArray[i] = NONE;
			}
			else
			{
				m_InputArray[i] = START;
			}
		}

		else
		{
			if (m_CurrentInputArray[i] == 0)
			{
				m_InputArray[i] = NONE;
			}
			else if (m_CurrentInputArray[i] == m_OldInputArray[i])
			{
				m_InputArray[i] = HOLD;
			}
			else
			{
				m_InputArray[i] = START;
			}
		}
	}

	// Key State ó��.
	for (int i = keyQ; i < idxNum; ++i)
	{
		CCAssert(((m_CurrentInputArray[i] == HOLD) || (m_OldInputArray[i] == HOLD)),
				"CurrentArray And OldArray Can't take value KEY_STATUS::HOLD");

		if (m_CurrentInputArray[i] == END)
		{
			m_InputArray[i] == END;
		}
		else if (m_CurrentInputArray[i] == START)
		{
			m_InputArray[i] == START;
		}
		else if ((m_CurrentInputArray[i] == NONE) && (m_OldInputArray[i] == START))
		{
			m_InputArray[i] == HOLD;
		}
		else
		{
			m_InputArray[i] == NONE;
		}
	}
}


/* 
	JoyStick���� ���� ��ǲ�� �ʿ� ������ ���� �Լ�.
	Init���� ������ deviceId�� ���ڷ� �޴´�. �� ��쿡�� padId.
	m_pMap->get�Լ����� ù ��° ���ڸ� ȣ���ϸ� ��ǲ�� �ִ��� �������� ���� �� �ִ�.
*/

void InputLayer::MapKeySetting(const unsigned int padId)
{
	// Receive Stick Input
	m_pMap->MapFloat(JoyStickX, padId, gainput::PadButton::PadButtonLeftStickX);
	m_pMap->MapFloat(JoyStickY, padId, gainput::PadButton::PadButtonLeftStickY);

	// Receive Button Input
	m_pMap->MapBool(joyA, padId, gainput::PadButton::PadButtonA);
	m_pMap->MapBool(joyB, padId, gainput::PadButton::PadButtonB);
	m_pMap->MapBool(joyX, padId, gainput::PadButton::PadButtonX);
	m_pMap->MapBool(joyStart, padId, gainput::PadButton::PadButtonStart);

	return;
}



/*
	Update �Լ� �ȿ��� JoyStick�� x, y���� ���ڷ� �޾Ƽ� ���´�.
	���� float�������� ���� x, y���� Ű����� ���� 8�������� �ٲپ� �����ϴ� �Լ�.
	�� �� ���� OldInputArray�� �����صΰ�, �� ���� ���� CurrentInputArray�� �޾��ش�.
*/

void InputLayer::ConvertJoyStickToUnitVec(float x, float y)
{
	if (x != 0)
	{
		m_OldInputArray[unitVecX] = m_CurrentInputArray[unitVecX];
		m_CurrentInputArray[unitVecX] = (x > 0) ? 1 : -1;
	}
	else
	{
		m_OldInputArray[unitVecX] = m_CurrentInputArray[unitVecX];
		m_CurrentInputArray[unitVecX] = 0;
	}

	if (y != 0)
	{
		m_OldInputArray[unitVecY] = m_CurrentInputArray[unitVecY];
		m_CurrentInputArray[unitVecY] = (y > 0) ? 1 : -1;
	}
	else
	{
		m_OldInputArray[unitVecY] = m_CurrentInputArray[unitVecY];
		m_CurrentInputArray[unitVecY] = 0;
	}

	return;
}


/*
	Update()���� JoyStick��ǲ�� �����ϰ� �׿� �´� ó���� ���ִ� �Լ�.
	��ƽ �Է��� �� ���� �޾� ConvertJoyStickToUnitVec�� �Ѱ��ش�.
	��ư �Է¿� ���ؼ��� ��ư�� ���ȴ��� Ȯ���ϴ� CheckBoolIsNew��
	��ư�� ���������� Ȯ���ϴ� CheckBoolIsDown�� ȣ���Ѵ�.
*/

void InputLayer::DetectJoyStickInput()
{
	auto joyStickX = m_pMap->GetFloat(JoyStickX);
	auto joyStickY = m_pMap->GetFloat(JoyStickY);

	ConvertJoyStickToUnitVec(joyStickX, joyStickY);

	CheckBoolIsNew();
	CheckBoolIsDown();

	return;
}


/*
	DetectJoyStickInput���� ȣ��Ǿ� ��ư�� ������ ���� ���� �����ϴ� �Լ�.
	������ �Ǹ� CurrentInputArray�� OldInputArray�� ���� �ٲپ� �ش�.
*/

void InputLayer::CheckBoolIsNew()
{
	if (m_pMap->GetBoolIsNew(joyA))
	{
		m_OldInputArray[joyA] = m_CurrentInputArray[joyA];
		m_CurrentInputArray[joyA] = START;
	}

	if (m_pMap->GetBoolIsNew(joyB))
	{
		m_OldInputArray[joyB] = m_CurrentInputArray[joyB];
		m_CurrentInputArray[joyB] = START;
	}
	
	if (m_pMap->GetBoolIsNew(joyX))
	{
		m_OldInputArray[joyX] = m_CurrentInputArray[joyX];
		m_CurrentInputArray[joyX] = START;
	}

	if (m_pMap->GetBoolIsNew(joyStart))
	{
		m_OldInputArray[joyStart] = m_CurrentInputArray[joyStart];
		m_CurrentInputArray[joyStart] = START;
	}

	return;
}

void InputLayer::CheckBoolIsDown()
{
	if (m_pMap->GetBoolWasDown(joyA))
	{
		m_OldInputArray[joyA] = m_CurrentInputArray[joyA];
		m_CurrentInputArray[joyA] = END;
	}

	if (m_pMap->GetBoolWasDown(joyB))
	{
		m_OldInputArray[joyB] = m_CurrentInputArray[joyB];
		m_CurrentInputArray[joyB] = END;
	}

	if (m_pMap->GetBoolWasDown(joyX))
	{
		m_OldInputArray[joyX] = m_CurrentInputArray[joyX];
		m_CurrentInputArray[joyX] = END;
	}

	if (m_pMap->GetBoolWasDown(joyStart))
	{
		m_OldInputArray[joyStart] = m_CurrentInputArray[joyStart];
		m_CurrentInputArray[joyStart] = END;
	}
	
	return;
}


/*
	Keyboard �Է��� �޾� ��ư�� ���� �������� ���� �����ϴ� �� ���� �ݹ� �Լ�.
	�⺻�����δ� CheckBoolIsNew, CheckBoolIsDown�� ���� ���� �Ѵ�.
*/

void InputLayer::onKeyPressed(EventKeyboard::KeyCode keyCode, Event *event)
{

	// ����Ű ���� ó��.
	if (keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW)
	{
		m_OldInputArray[unitVecY] = m_CurrentInputArray[unitVecY];
		m_CurrentInputArray[unitVecY] = 1;
	}
	if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW)
	{
		m_OldInputArray[unitVecY] = m_CurrentInputArray[unitVecY];
		m_CurrentInputArray[unitVecY] = -1;
	}
	if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
	{
		m_OldInputArray[unitVecX] = m_CurrentInputArray[unitVecX];
		m_CurrentInputArray[unitVecX] = 1;
	}
	if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
	{
		m_OldInputArray[unitVecX] = m_CurrentInputArray[unitVecX];
		m_CurrentInputArray[unitVecX] = -1;
	}


	// ��ư ���� ó��.
	if (keyCode == EventKeyboard::KeyCode::KEY_Q)
	{
		m_OldInputArray[keyQ] = m_CurrentInputArray[keyQ];
		m_CurrentInputArray[keyQ] = START;
	}
	if (keyCode == EventKeyboard::KeyCode::KEY_W)
	{
		m_OldInputArray[keyW] = m_CurrentInputArray[keyW];
		m_CurrentInputArray[keyW] = START;
	}
	if (keyCode == EventKeyboard::KeyCode::KEY_E)
	{
		m_OldInputArray[keyE] = m_CurrentInputArray[keyE];
		m_CurrentInputArray[keyE] = START;
	}
	if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE)
	{
		m_OldInputArray[keyESC] = m_CurrentInputArray[keyESC];
		m_CurrentInputArray[keyESC] = START;
	}

	return;
}

void InputLayer::onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event)
{
	// ����Ű ���� ó��.
	if (keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW)
	{
		m_OldInputArray[unitVecY] = m_CurrentInputArray[unitVecY];
		m_CurrentInputArray[unitVecY] = 0;
	}
	if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW)
	{
		m_OldInputArray[unitVecY] = m_CurrentInputArray[unitVecY];
		m_CurrentInputArray[unitVecY] = 0;
	}
	if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
	{
		m_OldInputArray[unitVecX] = m_CurrentInputArray[unitVecX];
		m_CurrentInputArray[unitVecX] = 0;
	}
	if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
	{
		m_OldInputArray[unitVecX] = m_CurrentInputArray[unitVecX];
		m_CurrentInputArray[unitVecX] = 0;
	}


	// ��ư ���� ó��.
	if (keyCode == EventKeyboard::KeyCode::KEY_Q)
	{
		m_OldInputArray[keyQ] = m_CurrentInputArray[keyQ];
		m_CurrentInputArray[keyQ] = END;
	}
	if (keyCode == EventKeyboard::KeyCode::KEY_W)
	{
		m_OldInputArray[keyW] = m_CurrentInputArray[keyW];
		m_CurrentInputArray[keyW] = END;
	}
	if (keyCode == EventKeyboard::KeyCode::KEY_E)
	{
		m_OldInputArray[keyE] = m_CurrentInputArray[keyE];
		m_CurrentInputArray[keyE] = END;
	}
	if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE)
	{
		m_OldInputArray[keyESC] = m_CurrentInputArray[keyESC];
		m_CurrentInputArray[keyESC] = END;
	}
}