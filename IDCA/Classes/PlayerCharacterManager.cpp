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
	//nt)memset(m_InputArray, NONE, stateIdxNum);fdf
	//nt)memset(m_InputUnitVec, NONE, vecIdxNum);

	if ((m_pCharacter = PlayerCharacter::create(fileName, fileExtention)) == nullptr)
	{
		m_pCharacter = PlayerCharacter::create(fileName, fileExtention);
	}
	
	m_pCharacter->setPosition(Vec2(100, 450));

	addChild(m_pCharacter);

	m_State = STATE::STOP;
	m_direction = DIRECTION::BOTTOM;

	scheduleUpdate();

	return true;
}

PlayerCharacter* PlayerCharacterManager::GetCharacter()
{
	return m_pCharacter;
}

int PlayerCharacterManager::getState()
{
	return m_State;
}

void PlayerCharacterManager::GetInput(int* input)
{
	m_pInput = input;
}

Vec2 PlayerCharacterManager::getPlayerPosition()
{
	return m_pCharacter->getPosition();
}

void PlayerCharacterManager::setPlayerPosition(Vec2 position,Vec2 backgroundPosition)
{

	if(m_pCharacter->GetState() == 0 || m_pCharacter->GetState() == 2)
	{
		m_pCharacter->setPosition(position);
		m_worldPosition = position - backgroundPosition;
	}
}

void PlayerCharacterManager::GetUnitVac(int * input)
{
	m_pUnitVec = input;
}

void PlayerCharacterManager::CalculatePlayerCharacterState()
{
	if (m_pCharacter->GetState() == STATE::ATTACK)
	{
		return;
	}
	else
	{
		if (m_pInput[INPUT_LAYER::ARRAY_INDEX::keyAttack] == INPUT_LAYER::KEY_STATUS::START
			|| m_pInput[INPUT_LAYER::ARRAY_INDEX::keyAttack] == INPUT_LAYER::KEY_STATUS::HOLD)
		{
			m_State = STATE::ATTACK;
		}
		else
		{
			if (m_pInput[INPUT_LAYER::ARRAY_INDEX::unitVecXStatus] == INPUT_LAYER::KEY_STATUS::NONE&&
				m_pInput[INPUT_LAYER::ARRAY_INDEX::unitVecYStatus] == INPUT_LAYER::KEY_STATUS::NONE)
			{
				m_State = STATE::STOP;
			}
			else if (m_pInput[INPUT_LAYER::ARRAY_INDEX::unitVecXStatus] == INPUT_LAYER::KEY_STATUS::HOLD ||
				m_pInput[INPUT_LAYER::ARRAY_INDEX::unitVecYStatus] == INPUT_LAYER::KEY_STATUS::HOLD)
			{
				m_State = STATE::MOVE;
			}
			else if (m_pInput[INPUT_LAYER::ARRAY_INDEX::unitVecXStatus] == INPUT_LAYER::KEY_STATUS::START ||
				m_pInput[INPUT_LAYER::ARRAY_INDEX::unitVecYStatus] == INPUT_LAYER::KEY_STATUS::START)
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
	if (m_pUnitVec[INPUT_LAYER::UNIT_VEC_INDEX::unitVecX] == 0 && m_pUnitVec[INPUT_LAYER::UNIT_VEC_INDEX::unitVecY] == 1)
	{
		m_direction = DIRECTION::TOP;
	}
	else if (m_pUnitVec[INPUT_LAYER::UNIT_VEC_INDEX::unitVecX] == 1 && m_pUnitVec[INPUT_LAYER::UNIT_VEC_INDEX::unitVecY] == 1)
	{
		m_direction = DIRECTION::TOP_RIGHT;
	}
	else if (m_pUnitVec[INPUT_LAYER::UNIT_VEC_INDEX::unitVecX] == 1 && m_pUnitVec[INPUT_LAYER::UNIT_VEC_INDEX::unitVecY] == 0)
	{
		m_direction = DIRECTION::RIGHT;
	}
	else if (m_pUnitVec[INPUT_LAYER::UNIT_VEC_INDEX::unitVecX] == 1 && m_pUnitVec[INPUT_LAYER::UNIT_VEC_INDEX::unitVecY] == -1)
	{
		m_direction = DIRECTION::BOTTOM_RIGHT;
	}
	else if (m_pUnitVec[INPUT_LAYER::UNIT_VEC_INDEX::unitVecX] == 0 && m_pUnitVec[INPUT_LAYER::UNIT_VEC_INDEX::unitVecY] == -1)
	{
		m_direction = DIRECTION::BOTTOM;
	}
	else if (m_pUnitVec[INPUT_LAYER::UNIT_VEC_INDEX::unitVecX] == -1 && m_pUnitVec[INPUT_LAYER::UNIT_VEC_INDEX::unitVecY] == -1)
	{
		m_direction = DIRECTION::BOTTOM_LEFT;
	}
	else if (m_pUnitVec[INPUT_LAYER::UNIT_VEC_INDEX::unitVecX] == -1 && m_pUnitVec[INPUT_LAYER::UNIT_VEC_INDEX::unitVecY] == 0)
	{
		m_direction = DIRECTION::LEFT;
	}
	else if (m_pUnitVec[INPUT_LAYER::UNIT_VEC_INDEX::unitVecX] == -1 && m_pUnitVec[INPUT_LAYER::UNIT_VEC_INDEX::unitVecY] == 1)
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
	char logBuffer1[100];
	sprintf(logBuffer1, "anchor x:%f anchor y:%f ", m_pCharacter->getAnchorPoint().x, m_pCharacter->getAnchorPoint().y);
	cocos2d::log(logBuffer1);
	sprintf(logBuffer1, "anchor x:%f anchor y:%f ", m_pCharacter->getPosition().x, m_pCharacter->getPosition().y);
	cocos2d::log(logBuffer1);
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