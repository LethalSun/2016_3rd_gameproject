#include "pch.h"
#include "PlayerCharacterManager.h"
#include "PlayerCharacter.h"
#include "InputLayer.h"

PlayerCharacterManager * PlayerCharacterManager::create(const char * fileName, const char * fileExtention)
{
	auto pManager = new(std::nothrow) PlayerCharacterManager();
	if (pManager && pManager->init(fileName, fileExtention))
	{
		pManager->autorelease();
		return pManager;
	}
	else
	{
		delete pManager;
		pManager = nullptr;
		return pManager;
	}
}

bool PlayerCharacterManager::init(const char * fileName, const char * fileExtention)
{
	if (!(Node::init()))
	{
		return false;
	}

	m_pCharacter = PlayerCharacter::create(fileName, fileExtention);
	addChild(m_pCharacter);

	m_State = STATE::STOP;
	m_direction = DIRECTION::BOTTOM;
}

PlayerCharacter* PlayerCharacterManager::GetCharacter()
{
	return m_pCharacter;
}


void PlayerCharacterManager::GetInput()
{
	auto m_Input = InputLayer::create();
	m_pInput = m_Input->m_InputArray;
}



void PlayerCharacterManager::CalculatePlayerCharacterState()
{
	if (m_pCharacter->GetState() == STATE::ATTACK)
	{
		return;
	}
	else
	{
		if (m_pInput[InputLayer::ARRAY_INDEX::keyQ] == InputLayer::KEY_STATUS::START)
		{
			m_State = STATE::ATTACK;
		}
		else
		{
			if (m_pInput[InputLayer::ARRAY_INDEX::unitVecXStatus] == InputLayer::KEY_STATUS::NONE&&
				m_pInput[InputLayer::ARRAY_INDEX::unitVecYStatus] == InputLayer::KEY_STATUS::NONE)
			{
				m_State = STATE::STOP;
			}
			else if (m_pInput[InputLayer::ARRAY_INDEX::unitVecXStatus] == InputLayer::KEY_STATUS::HOLD ||
				m_pInput[InputLayer::ARRAY_INDEX::unitVecYStatus] == InputLayer::KEY_STATUS::HOLD)
			{
				m_State = STATE::MOVE;
			}
			else if (m_pInput[InputLayer::ARRAY_INDEX::unitVecXStatus] == InputLayer::KEY_STATUS::START ||
				m_pInput[InputLayer::ARRAY_INDEX::unitVecYStatus] == InputLayer::KEY_STATUS::START)
			{
				m_State = STATE::MOVE;
			}
		}
	}
}

void PlayerCharacterManager::SetPlayerCharacterState()
{
	m_pCharacter->SetState(m_State);
}

void PlayerCharacterManager::CalculatePlayerCharacterDirection()
{
	if (m_pInput[InputLayer::ARRAY_INDEX::unitVecX] == 0 && m_pInput[InputLayer::ARRAY_INDEX::unitVecY] == 1)
	{
		m_direction = DIRECTION::TOP;
	}
	else if (m_pInput[InputLayer::ARRAY_INDEX::unitVecX] == 1 && m_pInput[InputLayer::ARRAY_INDEX::unitVecY] == 1)
	{
		m_direction = DIRECTION::TOP_RIGHT;
	}
	else if (m_pInput[InputLayer::ARRAY_INDEX::unitVecX] == 1 && m_pInput[InputLayer::ARRAY_INDEX::unitVecY] == 0)
	{
		m_direction = DIRECTION::RIGHT;
	}
	else if (m_pInput[InputLayer::ARRAY_INDEX::unitVecX] == 1 && m_pInput[InputLayer::ARRAY_INDEX::unitVecY] == -1)
	{
		m_direction = DIRECTION::BOTTOM_RIGHT;
	}
	else if (m_pInput[InputLayer::ARRAY_INDEX::unitVecX] == 0 && m_pInput[InputLayer::ARRAY_INDEX::unitVecY] == -1)
	{
		m_direction = DIRECTION::BOTTOM;
	}
	else if (m_pInput[InputLayer::ARRAY_INDEX::unitVecX] == -1 && m_pInput[InputLayer::ARRAY_INDEX::unitVecY] == -1)
	{
		m_direction = DIRECTION::BOTTOM_LEFT;
	}
	else if (m_pInput[InputLayer::ARRAY_INDEX::unitVecX] == -1 && m_pInput[InputLayer::ARRAY_INDEX::unitVecY] == 0)
	{
		m_direction = DIRECTION::LEFT;
	}
	else if (m_pInput[InputLayer::ARRAY_INDEX::unitVecX] == -1 && m_pInput[InputLayer::ARRAY_INDEX::unitVecY] == -1)
	{
		m_direction = DIRECTION::TOP_LEFT;
	}
}

void PlayerCharacterManager::SetPlayerCharacterDirection()
{
	m_pCharacter->SetDirection(m_direction);
}

void PlayerCharacterManager::update(float dt)
{
	CalculatePlayerCharacterState();
	SetPlayerCharacterState();
	CalculatePlayerCharacterDirection();
	SetPlayerCharacterDirection();
	m_pCharacter->update(dt);
}

PlayerCharacterManager::PlayerCharacterManager()
{
}

PlayerCharacterManager::~PlayerCharacterManager()
{
}