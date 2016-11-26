#pragma once
#include "cocos2d.h"

 // Json 파일로 변환전까지 임시로 쓰는 Define.h

namespace STATIC
{
	const cocos2d::Size visibleSize = cocos2d::Size(1024, 768);
	const float ATTACK_MINUS_VAL = 100.f;
	const float CHASING_MINUS_VAL = 300.f;
	const float ORIGIN_RANGE = 50.f;
}

enum Button
{
	LeftStickX,
	LeftStickY
};

const char PLAYER_SPRITE[] = "WalkingFront01.png";
const char PLAYER_PLIST[] = "Warrior.plist";



namespace ENEMY
{
	const int ENEMY_MAX_NUM = 20;
	enum ENEMY_TYPE
	{
		Choco,
		EnemyTypeNum
	};

	namespace CHOCO
	{
		// Sprite
		const char CHOCO_SPRITE[] = "Choco.png";
		const char CHOCO_ATTACK_SPRITE[] = "Choco_Attacking.png";

		// Member Variable
		const float SEARCHING_RANGE = 400.f;
		const float CHASING_RANGE = 500.f;
		const float ATTACK_RANGE = 150.f;
		const float INIT_WIDTH = 0.8f;
		const float INIT_HEIGHT = 0.8f;
		const float MOVE_SPEED = 200.f;
		const float HITTED_SPEED = 6000.f;
	}
}