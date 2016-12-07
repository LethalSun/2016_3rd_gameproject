#include "pch.h"
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

void EnemyState_Attack::startState(Enemy* enemy)
{
	CCLOG("Start Attack!");
	//enemy->SetSpriteToAttack();
}

void EnemyState_Attack::runState(Enemy* enemy, float dt)
{
	float distanceFromPlayer = enemy->getDistanceFromPlayer();
	float attackRange = enemy->getAttackRange();
	char buf[255];
	sprintf(buf, "[Attacking] playerDistance : %f, AttackRange : %f, this X : %f, this Y : %f", enemy->getDistanceFromPlayer(), enemy->getAttackRange(), enemy->getPosition().x, enemy->getPosition().y);
	CCLOG(buf);

	if (!isPlayerInAttackRange(attackRange, distanceFromPlayer))
	{
		enemy->changeState<EnemyState_Approach>();
	}
	else if (!enemy->getIsAttackedOnce() && !enemy->getIsEnemyPreemptive())
	{
		enemy->changeState<EnemyState_Waiting>();
	}
	else
	{
		CCLOG("Attack!");
	}

	return;
}

void EnemyState_Attack::endState(Enemy* enemy)
{
	CCLOG("End Attack!");
	//enemy->SetSpriteToCommon();
}
