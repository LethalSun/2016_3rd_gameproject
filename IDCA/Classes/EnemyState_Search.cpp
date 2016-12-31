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
}

void EnemyState_Search::runState(Enemy* enemy, float dt)
{
	if (isPlayerInSearchRange(enemy->getSearchingRange(), enemy->getDistanceFromPlayer()))
	{
		enemy->changeState<EnemyState_Approach>();
	}
}

void EnemyState_Search::endState(Enemy* enemy)
{
}

const int EnemyState_Search::returnStateNumber()
{
	return ENEMY_STATE_TYPE::SEARCHING;
}
