#include "pch.h"
#include "Enemy.h"
#include "BossState_Search.h"

/*
	BossState_Search
	������ ���� ���� ������� State.
	EnemyState�� �⺻�����δ� ������ ���������� �ٸ� ���� �� ���� �ִ�.
		1. Sleeping �Ǻ��� ����. (������ �⺻������ �����ִ� �����̹Ƿ�)
		2. ChangeState�� BossState���� ���ش�.
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
