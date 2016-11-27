#include "pch.h"
#include "InputLayer.h"

bool InputLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Vec2 WIN_SIZE(1024, 768);
	

	// Array 세팅.
	for (int i = unitVecX; i < idxNum; ++i)
	{
		m_CurrentInputArray[i] = NONE;
		m_OldInputArray[i] = NONE;
		m_InputArray[i] = NONE;
	}

	// JoyStick 세팅
	m_pMap = new gainput::InputMap(m_Manager);

	m_Manager.SetDisplaySize(WIN_SIZE.x, WIN_SIZE.y);
	const gainput::DeviceId padId = m_Manager.CreateDevice<gainput::InputDevicePad>();
	MapKeySetting(padId);


	// Keyboard 인풋을 받을 Listener 세팅.
	auto eventListener = EventListenerKeyboard::create();

	eventListener->onKeyPressed = CC_CALLBACK_2(InputLayer::onKeyPressed, this);
	eventListener->onKeyReleased = CC_CALLBACK_2(InputLayer::onKeyReleased, this);
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, this);

	scheduleUpdate();

	return true;
}


/*
	Update
	CurrentInputArray/OldInputArray에 대하여
		JoyStick 인풋을 받음. 값을 저장.
		Keyboard 인풋을 받음. 값을 저장. (리스너가 자동으로 받음)

	저장된 값을 바탕으로 InputArray의 값을 지정.
*/

void InputLayer::update(const float deltaTime)
{
	DetectJoyStickInput();
	DefineWhatIsInputValue();
}


/*
	DefineWhatIsInputValue
	CurrentInputArray와 OldInputArray를 비교하여 InputValue를 채워넣어주는 함수.
	기본적인 판별 알고리즘은
	UnitVec에 대해서 :
		Current값을 집어넣음.

	UnitVecStatus에 대해서 :		
		UnitVecX, Y 각각에 대하여,
		old(0) -> cur(0) : NONE
		old(0) -> cur(-1, 1) : START
		old(-1, 1) -> cur(0) : END
		old(-1 / 1) -> cur(-1 / 1) : HOLD (같은 방향일 경우)
		old(-1 / 1) -> cur(1 / -1) : START (다른 방향일 경우)

	Key에 대해서 :
		Cur(END)일 경우 : END
		Cur(START)일 경우 : START
		Cur(NONE)일 경우
			Old(START) -> HOLD

		else 상태 : NONE
*/

void InputLayer::DefineWhatIsInputValue()
{
	// UnitVec 처리
	for (int i = unitVecX; i <= unitVecY; ++i)
	{
		m_InputArray[i] = m_CurrentInputArray[i];
	}

	// UnitVecStatus 처리
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

	// Key State 처리.
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
	JoyStick에서 받을 인풋을 맵에 세팅해 놓는 함수.
	Init에서 생성한 deviceId를 인자로 받는다. 이 경우에는 padId.
	m_pMap->get함수에서 첫 번째 인자를 호출하면 인풋이 있는지 없는지를 받을 수 있다.
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
	Update 함수 안에서 JoyStick의 x, y값을 인자로 받아서 들어온다.
	현재 float방향으로 받은 x, y값을 키보드와 같은 8방향으로 바꾸어 저장하는 함수.
	그 전 값은 OldInputArray에 저장해두고, 그 현재 값은 CurrentInputArray에 받아준다.
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
	Update()에서 JoyStick인풋을 감지하고 그에 맞는 처리를 해주는 함수.
	스틱 입력은 그 값을 받아 ConvertJoyStickToUnitVec에 넘겨준다.
	버튼 입력에 대해서는 버튼이 눌렸는지 확인하는 CheckBoolIsNew와
	버튼이 떼어졌는지 확인하는 CheckBoolIsDown을 호출한다.
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
	DetectJoyStickInput에서 호출되어 버튼이 눌리고 떼는 것을 감지하는 함수.
	감지가 되면 CurrentInputArray와 OldInputArray의 값을 바꾸어 준다.
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
	Keyboard 입력을 받아 버튼이 떼고 눌러지는 것을 감지하는 두 개의 콜백 함수.
	기본적으로는 CheckBoolIsNew, CheckBoolIsDown과 같은 일을 한다.
*/

void InputLayer::onKeyPressed(EventKeyboard::KeyCode keyCode, Event *event)
{

	// 방향키 관련 처리.
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


	// 버튼 관련 처리.
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
	// 방향키 관련 처리.
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


	// 버튼 관련 처리.
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