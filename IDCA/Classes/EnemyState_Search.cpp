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
	char buf[1024];
	sprintf(buf, "[Searching] playerDistance : %f, searchingRange : %f, this X : %f, this Y : %f", enemy->getDistanceFromPlayer(), enemy->getSearchingRange(), enemy->getPosition().x, enemy->getPosition().y);
	CCLOG(buf);

	if (isPlayerInSearchRange(enemy->getSearchingRange(), enemy->getDistanceFromPlayer()))
	{
		enemy->changeState<EnemyState_Approach>();
	}
}

void EnemyState_Search::endState(Enemy* enemy)
{
	CCLOG("end_Searching!");
}

