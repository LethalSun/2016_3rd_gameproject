#include "pch.h"
#include "Enemy.h"
#include "EnemyState_Return.h"
#include "EnemyState_Approach.h"
#include "EnemyState_Search.h"

/*
Returning

���� ���¿��� Origin�� ���� UnitVec�� �ް�, �� �������� move�ϴ� ����.

1.       �÷��̾���� �Ÿ��� ChasingRange - 300������ ���, Approaching ���·� ����.
2.       Origin���� �Ÿ��� 50�ΰ��, Searching ���·� ����.

*/

void EnemyState_Return::startState(Enemy* enemy)
{
	CCLOG("Start Return!");
}


void EnemyState_Return::runState(Enemy* enemy, float dt)
{
	float distanceFromPlayer = enemy->getDistanceFromPlayer();
	float distanceFromOrigin = enemy->getDistanceFromOrigin();
	float chaseRange = enemy->getChasingRange();

	if (isPlayerInChasingRange(chaseRange, distanceFromPlayer))
	{
		enemy->changeState<EnemyState_Approach>();
	}
	// TODO :: json ���Ϸ� ����� ��ȯ��Ű��.
	else if (distanceFromOrigin < 50)
	{
		enemy->changeState<EnemyState_Search>();
	}
	else
	{
		enemy->CalUnitVecToOrigin();
		enemy->move(dt);
	}

	return;
}


void EnemyState_Return::endState(Enemy* enemy)
{
	CCLOG("End Return");
}
