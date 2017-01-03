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
const int MAX_HP = 300;
const int MAX_SP = 10;
const int ATTACK_DAMAGE = 30;

//아트로스 체력 공격력
const int ATROCE_MAX_HP = 20;
const int ATROCE_ATTACK_DAMAGE = 2;

//초코 체력 공격력
const int CHOCO_MAX_HP = 10;
const int CHOCO_ATTACK_DAMAGE = 1;

//보스 체력 공격력
const int ANCIENT_TREE_MAX_HP = 100;
const int ANCIENT_TREE_DAMAGE = 20;

// AncientTree State 상수들.
const float ANCIENT_TREE_RUSH_TIME = 2.f;
const int ANCIENT_TREE_ATTACK_NUMBER = 5;

const float ANCIENT_TREE_STRIKE_RELEASE_TIME = 3.f;
const float ANCIENT_TREE_STRIKE_SHRINK_TIME = 0.01f;
const float ANCIENT_TREE_STRIKE_RESTING_TIME = 0.1f;
const float ANCIENT_TREE_STRIKE_BIGGER_SCALE = 1.6;
const float ANCIENT_TREE_STRIKE_NORMAL_SCALE = 1.0;
const float STRIKE_DISTANCE = 45.f;
const int STRIKE_TENTACLE_NUMBER = 4;
const float STRIKE_CORRECTION_FLOAT = 0.7f;
const char ANCIENT_TREE_GROWL[] = "Sound/AncientTree_growl.wav";

const float ANCIENT_TREE_SUMMON_RANGE = 200.f;

const char DEAD_SCENE_LOST_SOUND[] = "EndingScene/LostGame.wav";
const char DEAD_SCENE_GAME_OVER_SOUND[] = "EndingScene/GameOverSound.wav";

const float DEAD_SCENE_BOUNCE_TIME = 3.0f;
const float DEAD_SCENE_REST_TIME = 0.3f;
const float DEAD_SCENE_FADE_IN_TIME = 1.f;

const char DEAD_SCENE_GAME_OVER_TITLE[] = "EndingScene/GameOver.png";
const char DEAD_SCENE_CHARACTER_WITH_LIGHT[] = "EndingScene/CharacterWithLight.png";
const char DEAD_SCENE_RESTART_TITLE[] = "EndingScene/Restart.png";
const float DEAD_SCENE_RESTART_TWINKLE_TIME = 2.0f;

const float DEAD_SCENE_TITLE_WIDTH = 0.5f;
const float DEAD_SCENE_TITLE_HEIGHT = 0.6f;
const float DEAD_SCENE_TITLE_JUMP_HEIGHT = 150.f;
const int DEAD_SCENE_TITLE_JUMP_NUMBER = 7;
const float DEAD_SCENE_TITLE_EASE_SPEED = 3.f;

const float DEAD_SCENE_CHARACTER_WIDTH = 0.5f;
const float DEAD_SCENE_CHARACTER_HEIGHT = 0.4f;

const float DEAD_SCENE_TEXT_WIDTH = 0.5f;
const float DEAD_SCENE_TEXT_HEIGHT = 0.2f;

const float ENDING_SCENE_TITLE_WIDTH = 0.5f;
const float ENDING_SCENE_TITLE_HEIGHT = 0.6f;
const float ENDING_SCENE_EASE_RATE = 3.0f;

const float ENDING_SCENE_TEXT_WIDTH = 0.5f;
const float ENDING_SCENE_TEXT_HEIGHT = 0.2f;

const char ENDING_SCENE_HOORAY_SOUND[] = "EndingScene/Hooray.wav";
const char ENDING_SCENE_BGM[] = "EndingScene/EndingBGM.wav";
const char ENDING_SCENE_YEAH_SOUND[] = "EndingScene/Yeah.wav";

const float ENDING_SCENE_RASIE_TIME = 1.5f;
const float ENDING_SCENE_REST_TIME = 0.3f;

const char ENDING_SCENE_VICTIORY_TITLE[] = "EndingScene/Victory.png";

const char ENDING_SCENE_RESTART_TEXT[] = "EndingScene/Restart.png";
const float ENDING_SCENE_RESTART_TWINKLE_TIME = 2.0f;

// Enemy
const float ENEMY_IGNORE_MOVE_RANGE = 0.05f;
const int ENEMY_EFFECT_MANAGER_ZORDER = 5;
const int ENEMY_ATTACK_SOUND_NUMBER = 5;

const int TINT_ACTION_TAG = 2;
const float ENEMY_RED_ACTION_TIME = 0.3f;

const float ANCIENT_TREE_RAGE30 = 0.3f;
const float ANCIENT_TREE_RAGE30_RATE = 0.7f;
const float ANCIENT_TREE_RAGE60 = 0.6f;
const float ANCIENT_TREE_RAGE60_RATE = 1.1f;

const float ANCIENT_TREE_SEARCHING_RANGE = 400.f;
const float ANCIENT_TREE_CHASING_RANGE = 400.f;
const float ANCIENT_TREE_ATTACKING_RANGE = 500.f;
const float ANCIENT_TREE_MOVE_SPEED = 5.f;
const float ANCIENT_TREE_STIFF_TIME = 0.0f;
const float ANCIENT_TREE_SUMMON_COOL_TIME = 5.f;
const float ANCIENT_TREE_ATTACK_FREQUENCY_INIT = 1.4f;

const char ANCIENT_TREE_NAME[] = "AncientTree";
const char ANCIENT_TREE_FILE_EXTENSION[] = ".png";
const char ANCIENT_TREE_ATTACK_SOUND[] = "Sound/AncientTree_hitGround.wav";
const char ANCIENT_TREE_HITED_SOUND[] = "Sound/AncientTree_hited.aiff";
const char ANCIENT_TREE_DYING_SOUND[] = "Sound/AncientTree_dying.wav";

const float CHOCO_SEARCHING_RANGE = 400.f;
const float CHOCO_CHASING_RANGE = 500.f;
const float CHOCO_ATTACKING_RANGE = 50.f;
const float CHOCO_MOVE_SPEED = 3.5f;
const float CHOCO_STIFF_TIME = 0.6f;

const char CHOCO_NAME[] = "Choco";
const char CHOCO_EXTENSION[] = ".png";
const char CHOCO_ATTACK_SOUND[] = "Sound/Choco_swing";
const char CHOCO_ATTACK_SOUND_EXTENSION[] = ".aif";
const char CHOCO_HITED_SOUND[] = "Sound/Choco_hited.mp3";
const char CHOCO_DYING_SOUND[] = "Sound/Choco_dying.wav";

const float ATROCE_SEARCHING_RANGE = 400.f;
const float ATROCE_CHASING_RANGE = 500.f;
const float ATROCE_ATTACKING_RANGE = 100.f;
const float ATROCE_MOVE_SPEED = 2.f;
const float ATROCE_STIFF_TIME = 0.6f;

const char ATROCE_ATTACK_SOUND[] = "Sound/Atroce_swing";
const char ATROCE_ATTACK_SOUND_EXTENSION[] = ".wav";
const char ATROCE_HITED_SOUND[] = "Sound/Atroce_hited.wav";
const char ATROCE_DYING_SOUND[] = "Sound/Atroce_dying.wav";

const char ATROCE_NAME[] = "Atroce";
const char ATROCE_EXTENSION[] = ".png";

// EnemyManager
const int STAGE_ONE_ENEMY_NUM = 20;
const char CHOCO_PLIST[] = "Choco.plist";
const char ATROCE_PLIST[] = "Atroce.plist";
const char ANCIENT_TREE_PLIST[] = "AncientTree.plist";
const char TRIGGER_SOUND[] = "Sound/StageOne_triggerOn.wav";

const float ENEMY_ATTACK_CORRECTION_VALUE = 50.f;

// Enemy State
const float ENEMY_PUSHED_DISTANCE = 75.f;
const int ENEMY_PUSHED_ACTION_TAG = 1;
const float ENEMY_PUSHED_CORRECTION_FLOAT = 0.3f;

const char PLAYER_FILE_NAME[] = "archbishop";
const char PLAYER_FILE_EXTENTION[] = ".png";

const int MAX_FRAME_NUM = 10;
const float ANIMATION_SPEED = 0.1f;
const float STOP_ANIMATION_SPEED = 0.005f;
const float ENEMY_ANIMATION_SPEED = 0.5f;
const float DEAD_STATE_FADEOUT_TIME = 1.5f;
const float DEAD_STATE_RESTING_TIME = 0.1f;

const float STATE_RETURN_END_RANGE = 50.f;
const float WAITING_SCENE_CORRECTION_VALUE = 50.f;

const int ANIMATION_TAG = 3;

// Scene
const char STAGE_ONE_BGM[] = "Sound/Forbidden.mp3";

// Tentacle
const float TENTACLE_ANIMAION_DELAY = 0.05f;
const int TENTACLE_MAX_FRAME_NUM = 10;
const float TENTACLE_FADE_IN_CORRECTION_VALUE = 1.2f;
const float TENTACLE_ATTACK_RANGE = 90.f;

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
	BOSS_ATTACK = 7, BOSS_STRIKE = 8, BOSS_RUSH = 9, BOSS_SUMMON = 10,
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

const char SKILL_NAME[] = "storm bolt";
const float MAX_COOL_TIME = 5.f;
const int SKILL_DAMAGE = 5;
const char SKILL_IMAGE[] = "Hammer.png";
const char SKILL_IMAGE_GRAY[] = "HammerGray.png";
const char PROJECTILE_IMAGE[] = "hammerProjectile.png";
const char DAMAGE_FONT[] = "Effect/damageFont.fnt";
const char EFFECT_IMAGE[] = "Effect/effect.png";
const float SKILL_DURATION = 1.f;
const float MAX_SKILL_RANGE = 400.f; // .=. sqrt(1280^2 + 720^2)
const float MAX_SKILL_COLIDE_RANGE = 70.f;
const float SKILL_ROTATE_TIME = 0.1f;
const float SKILL_ROTATE_DEGREE = 360.f;
const float SCALE_PROJECTILE = 2.f;



const char RETURNTOMAIN[] = "Return to Main";
const char RETURNTOGAME[] = "Return to Game";
const char ENEMYMOVERNAME[] = "Enemy Mover Component";
const char THUMBNAIL[] = "Board/archbishop.PNG";
const char MAXHPBAR[] = "Board/hpMax.png";
const char HPBAR[] = "Board/hp.png";
const char HAMMER[] = "Hammer.png";
const char HAMMERGRAY[] = "HammerGray.png";

const char HAMMERNAME[] = "Hammer";
const char HAMMERGRAYNAME[] = "Hammer Gray";


const float MenuPadding = 300.f;




const float EFFECT_POSITION_X = 0;
const float EFFECT_POSITION_Y = 50;


const float EFFECT_SCALE = 1.5f;

const float LABEL_POSITION_X = 30.f;
const float LABEL_POSITION_Y = 0.f;

const float LABEL_SCALE = 2.0f;
const float EFFECT_MOVE_TIME = 0.8f;
const float EFFECT_ELASTIC_TIME = 0.5f;

const float POSITIONOFHP_CHOCO_X =29.f;
const float POSITIONOFHP_CHOCO_Y = 36.f;

const float POSITIONOFHP_ATROCE_X = 80.f;
const float POSITIONOFHP_ATROCE_Y = 170.f;

const float POSITIONOFHP_ANCIENTTREE_X = 131.f;
const float POSITIONOFHP_ANCIENTTREE_Y = 150.f;

const float SIZEOFHP_X_CHOCO = 0.1f;
const float SIZEOFHP_Y_CHOCO = 0.1f;

const float SIZEOFHP_X_ATROCE = 0.3f;
const float SIZEOFHP_Y_ATROCE = 0.2f;

const float SIZEOFHP_X_ANCIENTTREE = 0.5f;
const float SIZEOFHP_Y_ANCIENTTREE = 0.5f;

const float ZEROVEC = 0;
const int SIZEOFTILE = 32;
const int ENDOFTILE = 0;

const int TILEGID_1_FALSE = 0;
const int TILEGID_2_TRUE = 0;

const int THUMBNAIL_SCALE = 2;

const float THUMNAIL_POSITION_X = 10.f;
const float THUMNAIL_POSITION_Y = 750.f;

const float MAX_ROTATE_NUMBER = 10;
