#include "pch.h"
#include "PlayerCharacterManager.h"
#include "PlayerCharacter.h"
#include "InputLayer.h"
#include <string>
PlayerCharacterManager::PlayerCharacterManager(const Vec2 AttackRange, const Vec2 BodyRange)
	:m_RedBoxTag(RED_BOX_TAG),
	m_GreenBoxTag(GREEN_BOX_TAG),
	m_AttackRange(AttackRange),
	m_BodyRange(BodyRange)
{
}

PlayerCharacterManager::~PlayerCharacterManager()
{
}

PlayerCharacterManager * PlayerCharacterManager::create(const char * fileName, const char * fileExtention)
{
	//각각의 직업마다 별도의 공격과피격범위를 지정해 주기 위한 부분
	PlayerCharacterManager* pManager;
	String filename = fileName;
	if (filename.compare("archbishop") == 0)
	{
		auto attackRange = Vec2(ARCHBISHOP_ATTACK_RANGE, ARCHBISHOP_ATTACK_RANGE);
		auto bodyRange = Vec2(ARCHBISHOP_BODY_RANGE_X, ARCHBISHOP_BODY_RANGE_Y);
		pManager = new(std::nothrow)PlayerCharacterManager(attackRange, bodyRange);
	}
	else if (filename.compare("Warrior") == 0)
	{
		auto attackRange = Vec2(WORRIOR_ATTACK_RANGE, WORRIOR_ATTACK_RANGE);
		auto bodyRange = Vec2(WORRIOR_BODY_RANGE_X, WORRIOR_BODY_RANGE_Y);
		pManager = new(std::nothrow)PlayerCharacterManager(attackRange, bodyRange);
	}

	//실제 크리에이트 부분
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
	if ((m_pCharacter == nullptr))
	{
		return false;
	}

	m_pCharacter->setPosition(Vec2(100, 450));
	m_worldPosition = Vec2(100, 450);

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

void PlayerCharacterManager::CalculateAnchorPointForCollide()
{
	CalculateBodyAnchorPoint();

	if (IsInputAttackState() == true)
	{
		CalculateAttackAnchorPoint();
	}
}

void PlayerCharacterManager::CalculateAttackAnchorPoint()
{
	//화면에서의 공격앵커포인트
	auto position = Vec2(0.f, 0.f);

	auto bodyPositionX = position.x;
	auto bodyPositionY = position.y;

	auto offsetX = (m_BodyRange.x / 2) + (m_AttackRange.x / 2);
	auto deltaX = UNIT_X[m_pCharacter->GetDirection()] * offsetX;
	auto attackPostionX = bodyPositionX + deltaX;

	auto offsetY = (m_BodyRange.y / 2) + (m_AttackRange.y / 2);
	auto deltaY = UNIT_Y[m_pCharacter->GetDirection()] * offsetY;
	auto attackPostionY = bodyPositionY + deltaY;

	m_AttackAnchorPointForDebugBox = Vec2(attackPostionX, attackPostionY);

	//실제 충돌용 어택 포인트
	position = m_worldPosition;

	bodyPositionX = position.x;
	bodyPositionY = position.y;

	attackPostionX = bodyPositionX + deltaX;
	attackPostionY = bodyPositionY + deltaY;

	m_AttackAnchorPoint = Vec2(attackPostionX, attackPostionY);
}

void PlayerCharacterManager::CalculateBodyAnchorPoint()
{
	//화면에서의 피격앵커포인트
	m_BodyAnchorPointForDebugBox = Vec2(0, 0);
	//실제 충돌용 피격포인트
	m_BodyAnchorPoint = m_worldPosition;
}

void PlayerCharacterManager::GetInput(int* input)
{
	m_pInput = input;
}

Vec2 PlayerCharacterManager::getPlayerPosition()
{
	return m_pCharacter->getPosition();
}

void PlayerCharacterManager::setPlayerPosition(Vec2 position, Vec2 backgroundPosition)
{
	if (m_pCharacter->GetState() == 0 || m_pCharacter->GetState() == 2)
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

	if (IsInputAttackState() == true)
	{
		m_State = STATE::ATTACK;
	}
	else
	{
		if (IsInputStopState() == true)
		{
			m_State = STATE::STOP;
		}
		else if (IsInputMoveStartState() == true)
		{
			m_State = STATE::MOVE;
		}
		else if (IsInputMoveHoldState() == true)
		{
			m_State = STATE::MOVE;
		}
	}
}

void PlayerCharacterManager::SetPlayerCharacterState()
{
	m_pCharacter->SetState(m_State);
}

void PlayerCharacterManager::CalculatePlayerCharacterDirection()
{
	if (m_pCharacter->GetState() == STATE::ATTACK)
	{
		return;
	}

	if (IsUnitVecTop() == true)
	{
		m_direction = DIRECTION::TOP;
	}
	else if (IsUnitVecTopRight() == true)
	{
		m_direction = DIRECTION::TOP_RIGHT;
	}
	else if (IsUnitVecRight() == true)
	{
		m_direction = DIRECTION::RIGHT;
	}
	else if (IsUnitVecBottomRight() == true)
	{
		m_direction = DIRECTION::BOTTOM_RIGHT;
	}
	else if (IsUnitVecBottom() == true)
	{
		m_direction = DIRECTION::BOTTOM;
	}
	else if (IsUnitVecBottomLeft() == true)
	{
		m_direction = DIRECTION::BOTTOM_LEFT;
	}
	else if (IsUnitVecLeft() == true)
	{
		m_direction = DIRECTION::LEFT;
	}
	else if (IsUnitVecTopLeft() == true)
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

	//여러가지 값 계산
	CalculatePlayerCharacterState();
	SetPlayerCharacterState();
	CalculatePlayerCharacterDirection();
	SetPlayerCharacterDirection();
	CalculateAnchorPointForCollide();

	//캐릭터 값 설정및 업데이트
	m_pCharacter->update(dt);
	m_pCharacter->SetAttackAnchorPointForMakeDebugBox(m_AttackAnchorPointForDebugBox);
	m_pCharacter->SetBodyAnchorPointForMakeDebugBox(m_BodyAnchorPointForDebugBox);
	m_pCharacter->SetAttackAnchorPoint(m_AttackAnchorPoint);
	m_pCharacter->SetBodyAnchorPoint(m_BodyAnchorPoint);
}

//상태,유닛벡터 조건 확인 함수

bool PlayerCharacterManager::IsInputAttackState()
{
	if (m_pInput[INPUT_LAYER::ARRAY_INDEX::keyAttack] == INPUT_LAYER::KEY_STATUS::START
		|| m_pInput[INPUT_LAYER::ARRAY_INDEX::keyAttack] == INPUT_LAYER::KEY_STATUS::HOLD)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool PlayerCharacterManager::IsInputStopState()
{
	if (m_pInput[INPUT_LAYER::ARRAY_INDEX::unitVecXStatus] == INPUT_LAYER::KEY_STATUS::NONE&&
		m_pInput[INPUT_LAYER::ARRAY_INDEX::unitVecYStatus] == INPUT_LAYER::KEY_STATUS::NONE)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool PlayerCharacterManager::IsInputMoveStartState()
{
	if (m_pInput[INPUT_LAYER::ARRAY_INDEX::unitVecXStatus] == INPUT_LAYER::KEY_STATUS::HOLD ||
		m_pInput[INPUT_LAYER::ARRAY_INDEX::unitVecYStatus] == INPUT_LAYER::KEY_STATUS::HOLD)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool PlayerCharacterManager::IsInputMoveHoldState()
{
	if (m_pInput[INPUT_LAYER::ARRAY_INDEX::unitVecXStatus] == INPUT_LAYER::KEY_STATUS::START ||
		m_pInput[INPUT_LAYER::ARRAY_INDEX::unitVecYStatus] == INPUT_LAYER::KEY_STATUS::START)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool PlayerCharacterManager::IsUnitVecTop()
{
	if (m_pUnitVec[INPUT_LAYER::UNIT_VEC_INDEX::unitVecX] == 0 && m_pUnitVec[INPUT_LAYER::UNIT_VEC_INDEX::unitVecY] == 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool PlayerCharacterManager::IsUnitVecTopRight()
{
	if (m_pUnitVec[INPUT_LAYER::UNIT_VEC_INDEX::unitVecX] == 1 && m_pUnitVec[INPUT_LAYER::UNIT_VEC_INDEX::unitVecY] == 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool PlayerCharacterManager::IsUnitVecRight()
{
	if (m_pUnitVec[INPUT_LAYER::UNIT_VEC_INDEX::unitVecX] == 1 && m_pUnitVec[INPUT_LAYER::UNIT_VEC_INDEX::unitVecY] == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool PlayerCharacterManager::IsUnitVecBottomRight()
{
	if (m_pUnitVec[INPUT_LAYER::UNIT_VEC_INDEX::unitVecX] == 1 && m_pUnitVec[INPUT_LAYER::UNIT_VEC_INDEX::unitVecY] == -1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool PlayerCharacterManager::IsUnitVecBottom()
{
	if (m_pUnitVec[INPUT_LAYER::UNIT_VEC_INDEX::unitVecX] == 0 && m_pUnitVec[INPUT_LAYER::UNIT_VEC_INDEX::unitVecY] == -1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool PlayerCharacterManager::IsUnitVecBottomLeft()
{
	if (m_pUnitVec[INPUT_LAYER::UNIT_VEC_INDEX::unitVecX] == -1 && m_pUnitVec[INPUT_LAYER::UNIT_VEC_INDEX::unitVecY] == -1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool PlayerCharacterManager::IsUnitVecLeft()
{
	if (m_pUnitVec[INPUT_LAYER::UNIT_VEC_INDEX::unitVecX] == -1 && m_pUnitVec[INPUT_LAYER::UNIT_VEC_INDEX::unitVecY] == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool PlayerCharacterManager::IsUnitVecTopLeft()
{
	if (m_pUnitVec[INPUT_LAYER::UNIT_VEC_INDEX::unitVecX] == -1 && m_pUnitVec[INPUT_LAYER::UNIT_VEC_INDEX::unitVecY] == 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}