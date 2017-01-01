#include "pch.h"
#include "Enemy.h"
#include "BossState_Attack.h"
#include "BossState_Strike.h"
#include "BossState_Rush.h"

/*
	BossState_Attack
	작성자 : 이근원
	Boss가 공격을 하는 상태.
	Boss내부의 공격 횟수가 가득 차면 Strike 상태로 돌입.
	만약 player가 공격 범위 바깥이라면 Rush 상태로 돌입.
*/

void BossState_Attack::startState(Enemy* enemy)
{
	return;
}

void BossState_Attack::runState(Enemy* enemy, float dt)
{
	auto attackNumber = enemy->getAttackNumber();

	// Player가 공격 거리내에 없다면 Rush상태로 변경.
	if (!isPlayerInAttackRange(enemy->getChasingRange(), enemy->getDistanceFromPlayer()))
	{
		enemy->changeState<BossState_Rush>();
	}
	// 3번 공격을 했다면 공격 회수 초기화 후 Strike 상태로 변경.
	else if (!(attackNumber % 3))
	{
		enemy->setAttackNumber(0);
		enemy->changeState<BossState_Strike>();
	}

	return;
}

void BossState_Attack::endState(Enemy* enemy)
{
	return;
}

const int BossState_Attack::returnStateNumber()
{
	return ENEMY_STATE_TYPE::BOSS_ATTACK;
}