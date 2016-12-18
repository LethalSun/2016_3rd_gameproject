#pragma once
#include "cocos2d.h"

//HW
enum STATE
{
	STOP = 0,
	ATTACK = 1,
	MOVE = 2,
	SKILL = 3
};

enum DIRECTION
{
	TOP,
	TOP_RIGHT,
	RIGHT,
	BOTTOM_RIGHT,
	BOTTOM,
	BOTTOM_LEFT,
	LEFT,
	TOP_LEFT,
};
//ĳ���� ü�� ���ݷ�
const int MAX_HP = 1000;
const int MAX_SP = 10;
const int ATTACK_DAMAGE = 3;

//��Ʈ�ν� ü�� ���ݷ�
const int ATROCE_MAX_HP = 10;
const int ATROCE_ATTACK_DAMAGE = 2;
//���� ü�� ���ݷ�
const int CHOCO_MAX_HP = 10;
const int CHOCO_ATTACK_DAMAGE = 1;

const char PLAYER_FILE_NAME[] = "archbishop";
const char PLAYER_FILE_EXTENTION[] = ".png";
//HW
// Json ���Ϸ� ��ȯ������ �ӽ÷� ���� Define.h

const int MAX_FRAME_NUM = 10;
const float ANIMATION_SPEED = 0.1f;
const float STOP_ANIMATION_SPEED = 0.005f;

//KW
namespace INPUT_LAYER
{
	/* const & enum values */
	enum ARRAY_INDEX
	{
		unitVecXStatus = 0, unitVecYStatus = 1,

		// Keyborad Input idx
		// ������� JoyStick A, B, X, Start
		keyAttack = 2, keySkillAttack = 3, keySkillDefence = 4, keyESC = 5,

		stateIdxNum = 6
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

	enum ARROW
	{
		UP = 0, DOWN = 1, RIGHT = 2, LEFT = 3, ARROW_NUM = 4
	};
}

enum ENEMY_TYPE
{
	CHOCO = 0,
	ATROCE = 1,
	ENEMY_TYPE_NUM = 2
};

namespace CONFIG_DEFAULT
{
	const int intError = -1;
	const float floatError = -1.f;
	const char stringError[6] = "ERROR";
}

enum ENEMY_STATE_TYPE
{
	SEARCHING = 0, APPROACHING = 1, ATTACKING = 2, WAITING = 3, RETURN = 4, STATE_NUM = 5
};

//���ݹ����� �ǰݹ����� ���� �±�
const int RED_BOX_TAG = 10;
const int GREEN_BOX_TAG = 11;
//ü�¹ٿ� mp�ٸ� ���� �±�
const int RED_BOX_SOLID_TAG = 12;
const int GREEN_BOX_SOLID_TAG = 13;
//��ũ��� �� ���ݹ���(���簢��) �ǰݹ����� ���ο� ����
const float ARCHBISHOP_ATTACK_RANGE = 35.f;
const float ARCHBISHOP_BODY_RANGE_X = 30.f;
const float ARCHBISHOP_BODY_RANGE_Y = 90.f;
//��Ʈ�ν� �� ���ݹ���(���簢��) �ǰݹ����� ���ο� ����
const float ATROCE_ATTACK_RANGE = 68.f;
const float ATROCE_BODY_RANGE_X = 80.f;
const float ATROCE_BODY_RANGE_Y = 120.f;
//���� �� ���ݹ���(���簢��) �ǰݹ����� ���ο� ����
const float CHOCO_ATTACK_RANGE = 20.f;
const float CHOCO_BODY_RANGE_X = 20.f;
const float CHOCO_BODY_RANGE_Y = 45.f;
//������ �� ���ݹ���(���簢��) �ǰݹ����� ���ο� ����
const float WORRIOR_ATTACK_RANGE = 50.f;
const float WORRIOR_BODY_RANGE_X = 25.f;
const float WORRIOR_BODY_RANGE_Y = 95.f;

//KW