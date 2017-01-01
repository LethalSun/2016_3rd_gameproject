#pragma once
#include "cocos2d.h"

enum STATE
{
	STOP = 0,
	ATTACK = 1,
	MOVE = 2,
	SKILL = 3
};

enum DIRECTION
{
	TOP = 0,
	TOP_RIGHT = 1,
	RIGHT = 2,
	BOTTOM_RIGHT = 3,
	BOTTOM = 4,
	BOTTOM_LEFT = 5,
	LEFT = 6,
	TOP_LEFT = 7,
};
//유닛벡터 배열
const int UNIT_X[8] = { 0,1,1,1,0,-1,-1,-1 };
const int UNIT_Y[8] = { 1,1,0,-1,-1,-1,0,1 };

//캐릭터 체력 공격력
const int MAX_HP = 1000;
const int MAX_SP = 10;
const int ATTACK_DAMAGE = 3;

//아트로스 체력 공격력
const int ATROCE_MAX_HP = 20;
const int ATROCE_ATTACK_DAMAGE = 2;

//초코 체력 공격력
const int CHOCO_MAX_HP = 10;
const int CHOCO_ATTACK_DAMAGE = 1;

//보스 체력 공격력
const int ANCIENT_TREE_MAX_HP = 350;
const int ANCIENT_TREE_DAMAGE = 10;

const char PLAYER_FILE_NAME[] = "archbishop";
const char PLAYER_FILE_EXTENTION[] = ".png";

// Json 파일로 변환전까지 임시로 쓰는 Define.h

const int MAX_FRAME_NUM = 10;
const float ANIMATION_SPEED = 0.1f;
const float STOP_ANIMATION_SPEED = 0.005f;

const int ANIMATION_TAG = 3;

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
	ANCIENT_TREE = 2,
	ENEMY_TYPE_NUM = 3
};

namespace CONFIG_DEFAULT
{
	const int intError = -1;
	const float floatError = -1.f;
	const char stringError[6] = "ERROR";
}

enum ENEMY_STATE_TYPE
{
	SEARCHING = 0, APPROACHING = 1, ATTACKING = 2, WAITING = 3, 
	RETURN = 4, BE_ATTACKED = 5, DEAD = 6, 
	BOSS_ATTACK =7, BOSS_STRIKE = 8, BOSS_RUSH = 9, BOSS_SUMMON = 10, 
	STATE_NUM = 11
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

// Ancient Tree의 공격범위
const float ANCIENT_TREE_ATTACK_RANGE = 50.f;
const float ANCIENT_TREE_BODY_RANGE_X = 40.f;
const float ANCIENT_TREE_BODY_RANGE_Y = 95.f;

//TEMP_DEFINE 옮긴곳.
namespace TEMP_DEFINE
{
	const int MAX_HP = 5;
	const int BOX_TAG_MONSTER = 2;
	const int BOX_TAG_CHARACTER = 1;
	const float ARCH_BISHOP_ATTACK_RANGE_X = 46.0f;
	const float ARCH_BISHOP_ATTACK_RANGE_Y = 76.0f;
	const int VELOCITY = 100;
	const int NUM_OF_SPRITE_FILE_PER_ACTIONS = 10;
	const float STOP_ANIMATION_SPEED = 0.005f;
	const float ANIMATION_SPEED = 0.1f;
	const float HIT_ANIMATION_SPEED = 0.03f;
	const int ATTACK_RANGE_X = 37;
	const int ATTACK_RANGE_Y = 47;

	const int MAP_MOVE_SPEED = 3;
	const int CHACRACTER_MOVE_SPEED = 3;
	const int MONSTER_MOVE_SPEED = 2;

	extern const char*ARCH_BISHOP_FILE_NAME;
	extern const char*SPRITE_FRAME_FILE_EXTENTION;
	extern const char *PLIST_FILE_NAME;
	extern const char* PLIST_NAME_2;

	extern const char*MAP_NAME1;
	extern const char*TILELAYER1;
	extern const char*TILELAYER2;
	extern const char*TILELAYER3;
	extern const char*TILELAYER4;
	extern const char*TILELAYER5;
	extern const char*OBJECTLAYER;
}