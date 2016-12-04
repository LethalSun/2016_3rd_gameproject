#include "pch.h"
#include "InputLayer.h"

using namespace INPUT_LAYER;

// TODO :: 다른 애들이 볼 필요 없으면 cpp로 가야한다. cpp의 맨 위로 넣자.
// JoyStick Mapping을 위한 값.

const int JoyStickX = 0;
const int JoyStickY = 1;

bool InputLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Vec2 WIN_SIZE(1024.f, 768.f);

	// TODO :: MEMSET 사용해서 초기화.
	// Array 세팅.
	(int)memset(m_CurrentInputArray, NONE, stateIdxNum);
	(int)memset(m_OldInputArray, NONE, stateIdxNum);
	(int)memset(m_CurrentInputUnitVec, NONE, UNIT_VEC_INDEX::vecIdxNum);
	(int)memset(m_OldInputUnitVec, NONE, UNIT_VEC_INDEX::vecIdxNum);
	(int)memset(m_InputArray, NONE, stateIdxNum);
	(int)memset(m_InputUnitVec, NONE, vecIdxNum);

	m_IsKeyboardPressed = false;

	// JoyStick 세팅
	// TODO :: Map 할당 해제해주기.
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
	m_Manager.Update();

	DefineWhatIsInputValue();
	InsertCurToOld();

	if (!m_IsKeyboardPressed)
	{
		DetectJoyStickInput();
	}
}

/*
	DefineWhatIsInputValue
	CurrentInputArray와 OldInputArray를 비교하여 InputValue를 채워넣어주는 함수.
	기본적인 판별 알고리즘은
	UnitVec에 대해서 :
		Current값을 집어넣음.


*/

void InputLayer::DefineWhatIsInputValue()
{
	// UnitVec 처리
	for (int i = unitVecX; i <= unitVecY; ++i)
	{
		m_InputUnitVec[i] = m_CurrentInputUnitVec[i];
	}

	// state 처리
	for (int i = unitVecXStatus; i < stateIdxNum; ++i)
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
	m_pMap->MapBool(keyAttack, padId, gainput::PadButton::PadButtonA);
	m_pMap->MapBool(keySkillAttack, padId, gainput::PadButton::PadButtonB);
	m_pMap->MapBool(keySkillDefence, padId, gainput::PadButton::PadButtonX);
	m_pMap->MapBool(keyESC, padId, gainput::PadButton::PadButtonStart);

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
		m_CurrentInputUnitVec[unitVecX] = (x > 0) ? 1 : -1;
		m_CurrentInputArray[unitVecXStatus] = START;
	}

	if (y != 0)
	{
		m_CurrentInputUnitVec[unitVecY] = (y > 0) ? 1 : -1;
		m_CurrentInputArray[unitVecYStatus] = START;
	}

	return;
}

/*
	GetInputArray / GetInputUnitVec
	private 멤버 Get함수.
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
	Update()에서 JoyStick인풋을 감지하고 그에 맞는 처리를 해주는 함수.
	스틱 입력은 그 값을 받아 ConvertJoyStickToUnitVec에 넘겨준다.
	버튼 입력에 대해서는 버튼이 눌렸는지 확인하는 CheckBoolIsNew와
	버튼이 떼어졌는지 확인하는 CheckBoolIsDown을 호출한다.
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
	DetectJoyStickInput에서 호출되어 버튼이 눌리고 떼는 것을 감지하는 함수.
	감지가 되면 CurrentInputArray와 OldInputArray의 값을 바꾸어 준다.
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
		m_CurrentInputArray[unitVecXStatus] = END;
		m_CurrentInputUnitVec[unitVecX] = 0;
	}
	if (m_pMap->GetBoolWasDown(JoyStickY))
	{
		m_CurrentInputArray[unitVecYStatus] = END;
		m_CurrentInputUnitVec[unitVecY] = 0;
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
	Keyboard 입력을 받아 버튼이 떼고 눌러지는 것을 감지하는 두 개의 콜백 함수.
	기본적으로는 CheckBoolIsNew, CheckBoolIsDown과 같은 일을 한다.
*/

void InputLayer::onKeyPressed(EventKeyboard::KeyCode keyCode, Event *event)
{

	m_IsKeyboardPressed = true;
	// 방향키 관련 처리.
	if (keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW)
	{
		m_CurrentInputUnitVec[unitVecY] = 1;
		m_CurrentInputArray[unitVecYStatus] = START;
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW)
	{
		m_CurrentInputUnitVec[unitVecY] = -1;
		m_CurrentInputArray[unitVecYStatus] = START;
	}
	
	
	if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
	{
		m_CurrentInputUnitVec[unitVecX] = 1;
		m_CurrentInputArray[unitVecXStatus] = START;
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
	{
		m_CurrentInputUnitVec[unitVecX] = -1;
		m_CurrentInputArray[unitVecXStatus] = START;
	}

	// 버튼 관련 처리.
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
	// 방향키 관련 처리.
	if (keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW)
	{
		m_CurrentInputUnitVec[unitVecY] = 0;
		m_CurrentInputArray[unitVecYStatus] = END;
	}
	if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW)
	{
		m_CurrentInputUnitVec[unitVecY] = 0;
		m_CurrentInputArray[unitVecYStatus] = END;
	}
	if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
	{
		m_CurrentInputUnitVec[unitVecX] = 0;
		m_CurrentInputArray[unitVecXStatus] = END;
	}
	if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
	{
		m_CurrentInputUnitVec[unitVecX] = 0;
		m_CurrentInputArray[unitVecXStatus] = END;
	}

	// 버튼 관련 처리.
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