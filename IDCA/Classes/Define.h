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
//캐릭터 체력 공격력
const int MAX_HP = 1000;
const int MAX_SP = 10;
const int ATTACK_DAMAGE = 3;

//아트로스 체력 공격력
const int ATROCE_MAX_HP = 10;
const int ATROCE_ATTACK_DAMAGE = 2;
//초코 체력 공격력
const int CHOCO_MAX_HP = 10;
const int CHOCO_ATTACK_DAMAGE = 1;

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

//공격범위와 피격범위를 위한 태그
const int RED_BOX_TAG = 10;
const int GREEN_BOX_TAG = 11;
//체력바와 mp바를 위한 태그
const int RED_BOX_SOLID_TAG = 12;
const int GREEN_BOX_SOLID_TAG = 13;
//아크비숍 의 공격범위(정사각형) 피격범위의 가로와 세로
const float ARCHBISHOP_ATTACK_RANGE = 35.f;
const float ARCHBISHOP_BODY_RANGE_X = 30.f;
const float ARCHBISHOP_BODY_RANGE_Y = 90.f;
//아트로스 의 공격범위(정사각형) 피격범위의 가로와 세로
const float ATROCE_ATTACK_RANGE = 68.f;
const float ATROCE_BODY_RANGE_X = 80.f;
const float ATROCE_BODY_RANGE_Y = 120.f;
//초코 의 공격범위(정사각형) 피격범위의 가로와 세로
const float CHOCO_ATTACK_RANGE = 20.f;
const float CHOCO_BODY_RANGE_X = 20.f;
const float CHOCO_BODY_RANGE_Y = 45.f;
//워리어 의 공격범위(정사각형) 피격범위의 가로와 세로
const float WORRIOR_ATTACK_RANGE = 50.f;
const float WORRIOR_BODY_RANGE_X = 25.f;
const float WORRIOR_BODY_RANGE_Y = 95.f;

//KW