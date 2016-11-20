#include "pch.h"
#include "Enemy.h"
#include "EnemyState_Search.h"
#include "EnemyState_Approach.h"


/*
	EnemyState_Search
	�÷��̾ SearchingRange�ȿ� ������ Approaching���·� ����.
	�� �������� Origin���� Searching ����.
*/

void EnemyState_Search::startState(Enemy* enemy)
{
	CCLOG("start_Searching!");
}

void EnemyState_Search::runState(Enemy* enemy, float dt)
{
	float distance = enemy->getDistanceFromPlayer();
	float searchRange = enemy->getSearchingRange();

	if (isPlayerInSearchRange(searchRange, distance))
	{
		enemy->changeState<EnemyState_Approach>();
	}
}

void EnemyState_Search::endState(Enemy* enemy)
{
	CCLOG("end_Searching!");
}

