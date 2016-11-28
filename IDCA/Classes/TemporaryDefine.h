#pragma once
//나중에 JSON이나 ini파일로 옮길내용.
namespace TEMP_DEFINE
{
	enum CHARACTER_STATE
	{
		STATE_STOP = 0,
		STATE_MOVE = 1,
		STATE_ATTACK = 2
	};

	enum INPUT
	{
		KEY_UP = 1,
		KEY_DOWN = 2,
		KEY_RIGHT = 4,
		KEY_LEFT = 8,
		KEY_A = 16
	};

	enum ACTIONS {
		NO_MOVE = 0,
		TOP = 1,
		BOTTOM = 2,
		RIGHT = 4,
		TOP_RIGTH = 5,
		BOTTOM_RIGHT = 6,
		LEFT = 8,
		TOP_LEFT = 9,
		BOTTOM_LEFT = 10,
		GET_DIRECTION_BIT = 15,
		ATTACK = 16,
		GET_ACTION_BIT = 240
	};
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
	extern const char*ARCH_BISHOP_FILE_NAME;
	extern const char*SPRITE_FRAME_FILE_EXTENTION;
	extern const char *PLIST_FILE_NAME;
	extern const char*MAP_NAME1;

}
