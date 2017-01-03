#include "pch.h"
#include "Enemy.h"
#include "BossState_Search.h"

/*
	BossState_Search
	보스를 위해 따로 만들어진 State.
	EnemyState와 기본적으로는 동일한 구조이지만 다른 점이 몇 가지 있다.
		1. Sleeping 판별이 없다. (보스는 기본적으로 깨어있는 상태이므로)
		2. ChangeState를 BossState에게 해준다.
*/

void BossState_Search::startState(Enemy* enemy)
{

}

void BossState_Search::runState(Enemy* enemy, float dt)
{

}

void BossState_Search::endState(Enemy* enemy)
{

}

const int BossState_Search::returnStateNumber()
{
	return ENEMY_STATE_TYPE::BOSS_SEARCHING;
}
