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

const char PLAYER_FILE_NAME[] = "archbishop";
const char PLAYER_FILE_EXTENTION[] = ".png";
//HW
// Json 파일로 변환전까지 임시로 쓰는 Define.h


const int MAX_FRAME_NUM = 10;
const float ANIMATION_SPEED = 0.1f;
const float STOP_ANIMATION_SPEED = 0.005f;

//KW
namespace INPUT_LAYER
{
	/* const & enum values */
	enum ARRAY_INDEX
	{
		// TODO :: ENUM값 명시적으로 표현 (unitVecX = 0, unitVecY = 1) 이런식으로.
		// ENUM은 하나로 빼서 한 곳에 모아 놓기. 헤더는 최대한 심플하게.
		// UnitVec은 키보드와 조이스틱 공용으로 관리 (-1, 0, 1)
		unitVecXStatus = 0, unitVecYStatus = 1,

		// Keyborad Input idx
		// 순서대로 JoyStick A, B, X, Start
		keyAttack = 2, keySkillAttack = 3, keySkillDefence = 4, keyESC = 5,

		stateIdxNum = 6

	};

	enum UNIT_VEC_INDEX
	{
		unitVecX = 0, unitVecY = 1,
		vecIdxNum = 2
	};

	// Key의 상태를 나타내줄 ENUM 값.
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