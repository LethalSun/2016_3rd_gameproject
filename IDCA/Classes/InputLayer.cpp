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

	Vec2 WIN_SIZE(1024, 768);

	// TODO :: MEMSET ����ؼ� �ʱ�ȭ.
	// Array ����.
	(int)memset(m_CurrentInputArray, NONE, stateIdxNum);
	(int)memset(m_OldInputArray, NONE, stateIdxNum);
	(int)memset(m_CurrentInputUnitVec, NONE, UNIT_VEC_INDEX::vecIdxNum);
	(int)memset(m_OldInputUnitVec, NONE, UNIT_VEC_INDEX::vecIdxNum);
	(int)memset(m_InputArray, NONE, stateIdxNum);
	(int)memset(m_InputUnitVec, NONE, vecIdxNum);

	Vec2 WIN_SIZE = Vec2(1024, 768);

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
		m_InputUnitVec[i] = m_CurrentInputUnitVec[i];
	}

	// UnitVecStatus ó��
	for (int i = unitVecXStatus; i <= unitVecYStatus; ++i)
	{
		if (m_OldInputUnitVec[i] == 0)
		{
			if (m_CurrentInputUnitVec[i] == 0)
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
			if (m_CurrentInputUnitVec[i] == 0)
			{
				m_InputArray[i] = NONE;
			}
			else if (m_CurrentInputUnitVec[i] == m_OldInputUnitVec[i])
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
	for (int i = keyAttack; i < stateIdxNum; ++i)
	{
		CCAssert(((m_CurrentInputArray[i] != HOLD) || (m_OldInputArray[i] != HOLD)),
				"CurrentArray And OldArray Can't take value KEY_STATUS::HOLD");

		if (m_CurrentInputArray[i] == END)
		{
			m_InputArray[i] = END;
		}
		else if (m_CurrentInputArray[i] == START)
		{
			m_InputArray[i] = START;
		}
		else if ((m_CurrentInputArray[i] == NONE) && (m_OldInputArray[i] == START))
		{
			m_InputArray[i] = HOLD;
		}
		else
		{
			m_InputArray[i] = NONE;
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
		m_OldInputUnitVec[unitVecX] = m_CurrentInputUnitVec[unitVecX];
		m_CurrentInputUnitVec[unitVecX] = (x > 0) ? 1 : -1;
	}
	else
	{
		m_OldInputUnitVec[unitVecX] = m_CurrentInputUnitVec[unitVecX];
		m_CurrentInputUnitVec[unitVecX] = 0;
	}

	if (y != 0)
	{
		m_OldInputUnitVec[unitVecY] = m_CurrentInputUnitVec[unitVecY];
		m_CurrentInputUnitVec[unitVecY] = (y > 0) ? 1 : -1;
	}
	else
	{
		m_OldInputUnitVec[unitVecY] = m_CurrentInputUnitVec[unitVecY];
		m_CurrentInputUnitVec[unitVecY] = 0;
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
	if (m_pMap->GetBoolIsNew(keyAttack))
	{
		m_OldInputArray[keyAttack] = m_CurrentInputArray[keyAttack];
		m_CurrentInputArray[keyAttack] = START;
	}

	if (m_pMap->GetBoolIsNew(keySkillAttack))
	{
		m_OldInputArray[keySkillAttack] = m_CurrentInputArray[keySkillAttack];
		m_CurrentInputArray[keySkillAttack] = START;
	}
	
	if (m_pMap->GetBoolIsNew(keySkillDefence))
	{
		m_OldInputArray[keySkillDefence] = m_CurrentInputArray[keySkillDefence];
		m_CurrentInputArray[keySkillDefence] = START;
	}

	if (m_pMap->GetBoolIsNew(keyESC))
	{
		m_OldInputArray[keyESC] = m_CurrentInputArray[keyESC];
		m_CurrentInputArray[keyESC] = START;
	}

	return;
}

void InputLayer::CheckBoolIsDown()
{
	if (m_pMap->GetBoolWasDown(keyAttack))
	{
		m_OldInputArray[keyAttack] = m_CurrentInputArray[keyAttack];
		m_CurrentInputArray[keyAttack] = END;
	}

	if (m_pMap->GetBoolWasDown(keySkillAttack))
	{
		m_OldInputArray[keySkillAttack] = m_CurrentInputArray[keySkillAttack];
		m_CurrentInputArray[keySkillAttack] = END;
	}

	if (m_pMap->GetBoolWasDown(keySkillDefence))
	{
		m_OldInputArray[keySkillDefence] = m_CurrentInputArray[keySkillDefence];
		m_CurrentInputArray[keySkillDefence] = END;
	}

	if (m_pMap->GetBoolWasDown(keyESC))
	{
		m_OldInputArray[keyESC] = m_CurrentInputArray[keyESC];
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
	// ����Ű ���� ó��.
	if (keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW)
	{
		m_OldInputUnitVec[unitVecY] = m_CurrentInputUnitVec[unitVecY];
		m_CurrentInputUnitVec[unitVecY] = 1;
	}
	if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW)
	{
		m_OldInputUnitVec[unitVecY] = m_CurrentInputUnitVec[unitVecY];
		m_CurrentInputUnitVec[unitVecY] = -1;
	}
	if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
	{
		m_OldInputUnitVec[unitVecX] = m_CurrentInputUnitVec[unitVecX];
		m_CurrentInputUnitVec[unitVecX] = 1;
	}
	if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
	{
		m_OldInputUnitVec[unitVecX] = m_CurrentInputUnitVec[unitVecX];
		m_CurrentInputUnitVec[unitVecX] = -1;
	}

	// ��ư ���� ó��.
	if (keyCode == EventKeyboard::KeyCode::KEY_Q)
	{
		m_OldInputArray[keyAttack] = m_CurrentInputArray[keyAttack];
		m_CurrentInputArray[keyAttack] = START;
	}
	if (keyCode == EventKeyboard::KeyCode::KEY_W)
	{
		m_OldInputArray[keySkillAttack] = m_CurrentInputArray[keySkillAttack];
		m_CurrentInputArray[keySkillAttack] = START;
	}
	if (keyCode == EventKeyboard::KeyCode::KEY_E)
	{
		m_OldInputArray[keySkillDefence] = m_CurrentInputArray[keySkillDefence];
		m_CurrentInputArray[keySkillDefence] = START;
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
		m_OldInputUnitVec[unitVecY] = m_CurrentInputUnitVec[unitVecY];
		m_CurrentInputUnitVec[unitVecY] = 0;
	}
	if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW)
	{
		m_OldInputUnitVec[unitVecY] = m_CurrentInputUnitVec[unitVecY];
		m_CurrentInputUnitVec[unitVecY] = 0;
	}
	if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
	{
		m_OldInputUnitVec[unitVecX] = m_CurrentInputUnitVec[unitVecX];
		m_CurrentInputUnitVec[unitVecX] = 0;
	}
	if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
	{
		m_OldInputUnitVec[unitVecX] = m_CurrentInputUnitVec[unitVecX];
		m_CurrentInputUnitVec[unitVecX] = 0;
	}

	// ��ư ���� ó��.
	if (keyCode == EventKeyboard::KeyCode::KEY_Q)
	{
		m_OldInputArray[keyAttack] = m_CurrentInputArray[keyAttack];
		m_CurrentInputArray[keyAttack] = END;
	}
	if (keyCode == EventKeyboard::KeyCode::KEY_W)
	{
		m_OldInputArray[keySkillAttack] = m_CurrentInputArray[keySkillAttack];
		m_CurrentInputArray[keySkillAttack] = END;
	}
	if (keyCode == EventKeyboard::KeyCode::KEY_E)
	{
		m_OldInputArray[keySkillDefence] = m_CurrentInputArray[keySkillDefence];
		m_CurrentInputArray[keySkillDefence] = END;
	}
	if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE)
	{
		m_OldInputArray[keyESC] = m_CurrentInputArray[keyESC];
		m_CurrentInputArray[keyESC] = END;
	}
}