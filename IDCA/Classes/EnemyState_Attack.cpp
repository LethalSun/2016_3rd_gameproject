#include "pch.h"
#include "SimpleAudioEngine.h"
#include "Enemy.h"
#include "EnemyState_Attack.h"
#include "EnemyState_Approach.h"
#include "EnemyState_Waiting.h"

/*

	Attacking

	Attack Range�ȿ� ���� ���, ������ �õ��ϴ� ����. ��������Ʈ ��ȯ.

	1.     �÷��̾���� �Ÿ��� Attack Range �̻��� ���, Approaching ���·� ����.
	2.     IsAttackedOnce�� False�� ���, Waiting���·� ����.

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