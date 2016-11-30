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

const int MAX_HP = 10;
const int MAX_SP = 10;
//HW
// Json ���Ϸ� ��ȯ������ �ӽ÷� ���� Define.h


const int MAX_FRAME_NUM = 10;
const float ANIMATION_SPEED = 0.1f;

//KW
namespace INPUT_LAYER
{
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
//KW