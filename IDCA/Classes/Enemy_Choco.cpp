#include "pch.h"
#include "Enemy_Choco.h"
#include "EnemyState_Search.h"
#include "Config.h"
#include "AnimationMaker.h"

const float Choco_SearchingRange = 400.f;
const float Choco_ChasingRange = 500.f;
const float Choco_AttackRange = 50.f;
const float Choco_MoveSpeed = 3.5f;
const float Choco_StiffTime = 0.6f;


const char Choco_Name[] = "Choco";
const char Choco_Extention[] = ".png";
const char Choco_AttackSound[] = "Sound/Choco_swing";
const char Choco_AttackSoundExtension[] = ".aif";
const char Choco_HitedSound[] = "Sound/Choco_hited.mp3";
const char Choco_DyingSound[] = "Sound/Choco_dying.wav";


bool Enemy_Choco::init(const Vec2 initPosition)
{
	if (!Enemy::init(initPosition))
	{
		return false;
	}

	setSearchingRange(Choco_SearchingRange);
	setChasingRange(Choco_ChasingRange);
	setAttackRange(Choco_AttackRange);
	setMoveSpeed(Choco_MoveSpeed);
	setIsAttackedOnce	(false);
	setStiffTime(Choco_StiffTime);

	auto AttackRangeChoco = Vec2(CHOCO_ATTACK_RANGE, CHOCO_ATTACK_RANGE);
	setAttackRangeForCollide(AttackRangeChoco);
	auto BodyRangeChoco = Vec2(CHOCO_BODY_RANGE_X, CHOCO_BODY_RANGE_Y);
	setBodyRangeForCollide(BodyRangeChoco);
	setIsAttackedOnce(false);
	setIsEnemyPreemptive(true);

	setHP(CHOCO_MAX_HP);
	setMaxHP(CHOCO_MAX_HP);
	setDamage(CHOCO_ATTACK_DAMAGE);

	// Sound 세팅
	setAttackSound(Choco_AttackSound);
	setAttackSoundExtension(Choco_AttackSoundExtension);
	setHitedSound(Choco_HitedSound);
	setDyingSound(Choco_DyingSound);

	// AnimationMaker 세팅.
	m_pAnimationMaker = AnimationMaker::create(Choco_Name, Choco_Extention);
	addChild(m_pAnimationMaker);
	m_pAnimationMaker->SetAnimationStop();
	m_pAnimationMaker->AddAnimation(getDirection());

	changeState<EnemyState_Search>();
	setBeforeState(getState());
	positiionOfHp = Vec2(29, 36);
	sizeOfHp_x = 0.1;
	sizeOfHp_y = 0.2;

	scheduleUpdate();
	return true;
}
