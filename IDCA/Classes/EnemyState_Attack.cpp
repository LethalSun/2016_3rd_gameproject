#include "pch.h"
#include "SimpleAudioEngine.h"
#include "Enemy.h"
#include "EnemyState_Attack.h"
#include "EnemyState_Approach.h"
#include "EnemyState_Waiting.h"

/*

	Attacking

	Attack Range안에 들어온 경우, 공격을 시도하는 상태. 스프라이트 전환.

	1.     플레이어와의 거리가 Attack Range 이상인 경우, Approaching 상태로 돌입.
	2.     IsAttackedOnce가 False인 경우, Waiting상태로 돌입.

*/

const float ATTACK_CORRECTION_VALUE = 50.f;

void EnemyState_Attack::startState(Enemy* enemy)
{
	CCLOG("Start Attack!");
}

void EnemyState_Attack::runState(Enemy* enemy, float dt)
{
	float distanceFromPlayer = enemy->getDistanceFromPlayer();
	float attackRange = enemy->getAttackRange();
	enemy->CalUnitVecToPlayer();
	enemy->TranslateUnitVec(enemy->getUnitVecToPlayer());
	enemy->CalDirection(enemy->getTranslatedUnitVec());

	if (!isPlayerInAttackRange(attackRange + ATTACK_CORRECTION_VALUE, distanceFromPlayer))
	{
		enemy->changeState<EnemyState_Approach>();
	}
	else if (!enemy->getIsAttackedOnce() && !enemy->getIsEnemyPreemptive())
	{
		enemy->changeState<EnemyState_Waiting>();
	}
	else
	{
		//enemy->setAttackChecked(false);
		CCLOG("Attack!");
	}

	return;
}

void EnemyState_Attack::endState(Enemy* enemy)
{
	CCLOG("End Attack!");
}

const int EnemyState_Attack::returnStateNumber()
{
	return ENEMY_STATE_TYPE::ATTACKING;
}