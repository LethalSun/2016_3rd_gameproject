#include "pch.h"
#include "InputLayer.h"

using namespace INPUT_LAYER;

// TODO :: �ٸ� �ֵ��� �� �ʿ� ������ cpp�� �����Ѵ�. cpp�� �� ���� ����.
// JoyStick Mapping�� ���� ��.

const int JoyStickX = 0;
const int JoyStickY = 1;

bool InputLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Vec2 WIN_SIZE(1024.f, 768.f);

	// TODO :: MEMSET ����ؼ� �ʱ�ȭ.
	// Array ����.
	(int)memset(m_CurrentInputArray, NONE, stateIdxNum);
	(int)memset(m_OldInputArray, NONE, stateIdxNum);
	(int)memset(m_CurrentInputUnitVec, NONE, UNIT_VEC_INDEX::vecIdxNum);
	(int)memset(m_OldInputUnitVec, NONE, UNIT_VEC_INDEX::vecIdxNum);
	(int)memset(m_InputArray, NONE, stateIdxNum);
	(int)memset(m_InputUnitVec, NONE, vecIdxNum);
	(int)memset(m_ArrowContainer, NONE, ARROW_NUM);

	m_IsKeyboardPressed = false;

	// JoyStick ����
	// TODO :: Map �Ҵ� �������ֱ�.
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
	DefineWhatIsUnitVec();
	DefineWhatIsInputValue();
	InsertCurToOld();

	/* State Log part */
	char logBuffer1[256];
	sprintf(logBuffer1, "%d%d%d%d%d%d %d%d, Arrow %d%d%d%d, unitVecStateX %d%d",
		m_InputArray[0],
		m_InputArray[1],
		m_InputArray[2],
		m_InputArray[3],
		m_InputArray[4],
		m_InputArray[5],

		m_InputUnitVec[0],
		m_InputUnitVec[1],

		m_ArrowContainer[0],
		m_ArrowContainer[1],
		m_ArrowContainer[2],
		m_ArrowContainer[3],

		m_OldInputArray[0],
		m_CurrentInputArray[0]
		);
	
	cocos2d::log(logBuffer1);

	m_Manager.Update();
	if (!m_IsKeyboardPressed)
	{
		DetectJoyStickInput();
	}
}

/*
	DefineWhatIsInputValue
	CurrentInputArray�� OldInputArray�� ���Ͽ� InputValue�� ä���־��ִ� �Լ�.
*/

void InputLayer::DefineWhatIsInputValue()
{
	// UnitVec ó��
	for (int i = unitVecX; i <= unitVecY; ++i)
	{
		m_InputUnitVec[i] = m_CurrentInputUnitVec[i];
	}

	// UnitVec State ó��
	for (int i = unitVecXStatus; i <= unitVecYStatus; ++i)
	{
		if ((m_CurrentInputArray[i] == 1) && (m_CurrentInputArray[i] == 1) && (m_InputArray[i] != START) && (m_InputArray[i] != HOLD))
		{
			m_InputArray[i] = START;
		}
		else if ((m_CurrentInputArray[i] == 1) && (m_CurrentInputArray[i] == 1) && ((m_InputArray[i] == START) || (m_InputArray[i] == HOLD)))
		{
			m_InputArray[i] = HOLD;
		}
		else if (((m_InputArray[i] == HOLD) || (m_InputArray[i] == START)) && (m_CurrentInputArray[i] == 0))
		{
			m_InputArray[i] = END;
		}
		else
		{
			m_InputArray[i] = NONE;
		}
	}

	// key state ó��
	for (int i = keyAttack; i < stateIdxNum; ++i)
	{
		if (m_CurrentInputArray[i] == END || m_OldInputArray[i] == END)
		{
			m_InputArray[i] = END;
			m_CurrentInputArray[i] = NONE;
		}
		else if (m_CurrentInputArray[i] == START)
		{
			m_InputArray[i] = START;
			m_CurrentInputArray[i] = NONE;
		}
		else if ((m_InputArray[i] == START && m_CurrentInputArray[i] == NONE) || m_InputArray[i] == HOLD)
		{
			m_InputArray[i] = HOLD;
		}
		else
		{
			m_InputArray[i] = NONE;
		}
	}
	return;
}

bool InputLayer::IsArrowContainerEmpty()
{
	if (!m_ArrowContainer[ARROW::UP] && !m_ArrowContainer[ARROW::DOWN] && !m_ArrowContainer[ARROW::RIGHT] && !m_ArrowContainer[ARROW::LEFT])
	{
		return true;
	}
	return false;
}

/*
	ArrowContainer�� �ִ� ������ �������� CurrentInputUnitVec�� �ٲپ� �ִ� �Լ�.
*/

void InputLayer::DefineWhatIsUnitVec()
{
	if (IsArrowContainerEmpty())
	{
		m_CurrentInputUnitVec[unitVecX] = 0;
		m_CurrentInputUnitVec[unitVecY] = 0;
	}

	if (m_ArrowContainer[ARROW::UP])
	{
		if (m_ArrowContainer[ARROW::DOWN])
		{
			m_CurrentInputUnitVec[unitVecY] = 0;
			m_CurrentInputArray[unitVecYStatus] = NONE;
		}
		else
		{
			m_CurrentInputUnitVec[unitVecY] = 1;
			m_CurrentInputArray[unitVecYStatus] = START;
		}
	}
	else if (m_ArrowContainer[ARROW::DOWN])
	{
		if (m_ArrowContainer[ARROW::UP])
		{
			m_CurrentInputUnitVec[unitVecY] = 0;
			m_CurrentInputArray[unitVecYStatus] = NONE;
		}
		else
		{
			m_CurrentInputUnitVec[unitVecY] = -1;
			m_CurrentInputArray[unitVecYStatus] = START;
		}
	}
	else
	{
		m_CurrentInputUnitVec[unitVecY] = 0;
		m_CurrentInputArray[unitVecYStatus] = NONE;
	}

	if (m_ArrowContainer[ARROW::RIGHT])
	{
		if (m_ArrowContainer[ARROW::LEFT])
		{
			m_CurrentInputUnitVec[unitVecX] = 0;
			m_CurrentInputArray[unitVecXStatus] = NONE;
		}
		else
		{
			m_CurrentInputUnitVec[unitVecX] = 1;
			m_CurrentInputArray[unitVecXStatus] = START;
		}
	}
	else if (m_ArrowContainer[ARROW::LEFT])
	{
		if (m_ArrowContainer[ARROW::RIGHT])
		{
			m_CurrentInputUnitVec[unitVecX] = 0;
			m_CurrentInputArray[unitVecXStatus] = NONE;
		}
		else
		{
			m_CurrentInputUnitVec[unitVecX] = -1;
			m_CurrentInputArray[unitVecXStatus] = START;
		}
	}
	else
	{
		m_CurrentInputUnitVec[unitVecX] = 0;
		m_CurrentInputArray[unitVecXStatus] = NONE;
	}

	return;
}


bool InputLayer::IsJoyStickButtonPressed()
{
	if (m_pMap->GetBool(keyAttack) || m_pMap->GetBool(keySkillAttack) || m_pMap->GetBool(keySkillDefence) || m_pMap->GetBool(keyESC))
	{
		return true;
	}

	return false;
}

void InputLayer::InsertCurToOld()
{

	for (int i = unitVecXStatus; i < stateIdxNum; ++i)
	{
		m_OldInputArray[i] = m_CurrentInputArray[i];
	}

	for (int i = unitVecX; i < vecIdxNum; ++i)
	{
		m_OldInputUnitVec[i] = m_CurrentInputUnitVec[i];
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
	m_pMap->MapBool(keyAttack, padId, gainput::PadButton::PadButtonA);
	m_pMap->MapBool(keySkillAttack, padId, gainput::PadButton::PadButtonB);
	m_pMap->MapBool(keySkillDefence, padId, gainput::PadButton::PadButtonX);
	m_pMap->MapBool(keyESC, padId, gainput::PadButton::PadButtonStart);

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
		if (x > 0)
		{
			m_ArrowContainer[ARROW::RIGHT] = 1;
		}
		else
		{
			m_ArrowContainer[ARROW::LEFT] = 1;
		}
	}

	if (y != 0)
	{
		if (y > 0)
		{
			m_ArrowContainer[ARROW::UP] = 1;
		}
		else
		{
			m_ArrowContainer[ARROW::DOWN] = 1;
		}
	}

	return;
}

/*
	GetInputArray / GetInputUnitVec
	private ��� Get�Լ�.
*/

int* InputLayer::GetInputArray()
{
	return m_InputArray;
}

int* InputLayer::GetInputUnitVec()
{
	return m_InputUnitVec;
}

/*
	Update()���� JoyStick��ǲ�� �����ϰ� �׿� �´� ó���� ���ִ� �Լ�.
	��ƽ �Է��� �� ���� �޾� ConvertJoyStickToUnitVec�� �Ѱ��ش�.
	��ư �Է¿� ���ؼ��� ��ư�� ���ȴ��� Ȯ���ϴ� CheckBoolIsNew��
	��ư�� ���������� Ȯ���ϴ� CheckBoolIsDown�� ȣ���Ѵ�.
*/

void InputLayer::DetectJoyStickInput()
{
	float inputX = 0;
	float inputY = 0;

	CheckBoolIsNew(&inputX, &inputY);
	ConvertJoyStickToUnitVec(inputX, inputY);
	CheckBoolIsDown(&inputX, &inputY);

	return;
}



/*
	DetectJoyStickInput���� ȣ��Ǿ� ��ư�� ������ ���� ���� �����ϴ� �Լ�.
	������ �Ǹ� CurrentInputArray�� OldInputArray�� ���� �ٲپ� �ش�.
*/

void InputLayer::CheckBoolIsNew(float* inputX, float* inputY)
{
	if (m_pMap->GetBoolIsNew(JoyStickX))
	{
		*inputX = m_pMap->GetFloat(JoyStickX);
	}
	if (m_pMap->GetBoolIsNew(JoyStickY))
	{
		*inputY = m_pMap->GetFloat(JoyStickY);
	}
	if (m_pMap->GetBoolIsNew(keyAttack))
	{
		m_CurrentInputArray[keyAttack] = START;
	}

	if (m_pMap->GetBoolIsNew(keySkillAttack))
	{
		m_CurrentInputArray[keySkillAttack] = START;
	}

	if (m_pMap->GetBoolIsNew(keySkillDefence))
	{
		m_CurrentInputArray[keySkillDefence] = START;
	}

	if (m_pMap->GetBoolIsNew(keyESC))
	{
		m_CurrentInputArray[keyESC] = START;
	}

	return;
}

void InputLayer::CheckBoolIsDown(float* inputX, float* inputY)
{
	if (m_pMap->GetBoolWasDown(JoyStickX))
	{
		m_ArrowContainer[ARROW::RIGHT] = 0;
		m_ArrowContainer[ARROW::LEFT] = 0;
	}

	if (m_pMap->GetBoolWasDown(JoyStickY))
	{
		m_ArrowContainer[ARROW::UP] = 0;
		m_ArrowContainer[ARROW::DOWN] = 0;
	}

	if (m_pMap->GetBoolWasDown(keyAttack))
	{
		m_CurrentInputArray[keyAttack] = END;
	}

	if (m_pMap->GetBoolWasDown(keySkillAttack))
	{
		m_CurrentInputArray[keySkillAttack] = END;
	}

	if (m_pMap->GetBoolWasDown(keySkillDefence))
	{
		m_CurrentInputArray[keySkillDefence] = END;
	}

	if (m_pMap->GetBoolWasDown(keyESC))
	{
		m_CurrentInputArray[keyESC] = END;
	}

	return;
}

/*
	Keyboard �Է��� �޾� ��ư�� ���� �������� ���� �����ϴ� �� ���� �ݹ� �Լ�.
	�⺻�����δ� CheckBoolIsNew, CheckBoolIsDown�� ���� ���� �Ѵ�.
*/

void InputLayer::onKeyPressed(EventKeyboard::KeyCode keyCode, Event *event)
{
	m_IsKeyboardPressed = true;
	// ����Ű ���� ó��.
	if (keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW)
	{
		m_ArrowContainer[ARROW::UP] = 1;
	}
	if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW)
	{
		m_ArrowContainer[ARROW::DOWN] = 1;
	}
	if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
	{
		m_ArrowContainer[ARROW::RIGHT] = 1;
	}
	if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
	{
		m_ArrowContainer[ARROW::LEFT] = 1;
	}

	// ��ư ���� ó��.
	if (keyCode == EventKeyboard::KeyCode::KEY_Q)
	{
		m_CurrentInputArray[keyAttack] = START;
	}
	if (keyCode == EventKeyboard::KeyCode::KEY_W)
	{
		m_CurrentInputArray[keySkillAttack] = START;
	}
	if (keyCode == EventKeyboard::KeyCode::KEY_E)
	{
		m_CurrentInputArray[keySkillDefence] = START;
	}
	if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE)
	{
		m_CurrentInputArray[keyESC] = START;
	}

	return;
}

void InputLayer::onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event)
{
	// ����Ű ���� ó��.
	if (keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW)
	{
		m_ArrowContainer[ARROW::UP] = 0;
	}
	if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW)
	{
		m_ArrowContainer[ARROW::DOWN] = 0;
	}
	if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
	{
		m_ArrowContainer[ARROW::RIGHT] = 0;
	}
	if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
	{
		m_ArrowContainer[ARROW::LEFT] = 0;
	}

	// ��ư ���� ó��.
	if (keyCode == EventKeyboard::KeyCode::KEY_Q)
	{
		m_CurrentInputArray[keyAttack] = END;
	}
	if (keyCode == EventKeyboard::KeyCode::KEY_W)
	{
		m_CurrentInputArray[keySkillAttack] = END;
	}
	if (keyCode == EventKeyboard::KeyCode::KEY_E)
	{
		m_CurrentInputArray[keySkillDefence] = END;
	}
	if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE)
	{
		m_CurrentInputArray[keyESC] = END;
	}

	m_IsKeyboardPressed = false;

	return;
}