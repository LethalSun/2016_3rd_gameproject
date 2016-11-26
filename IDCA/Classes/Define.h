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
//HW
enum Button
{
	LeftStickX,
	LeftStickY
};

const char PLAYER_SPRITE[] = "WalkingFront01.png";
const char PLAYER_PLIST[] = "Warrior.plist";
const int MAX_FRAME_NUM = 10;
const float ANIMATION_SPEED = 0.1f;