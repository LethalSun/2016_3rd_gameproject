#include "pch.h"
#include "Enemy.h"
#include "BossState_Attack.h"
#include "BossState_Strike.h"
#include "BossState_Rush.h"

/*
	BossState_Attack
	�ۼ��� : �̱ٿ�
	Boss�� ������ �ϴ� ����.
	Boss������ ���� Ƚ���� ���� ���� Strike ���·� ����.
	���� player�� ���� ���� �ٱ��̶�� Rush ���·� ����.
*/

void BossState_Attack::startState(Enemy* enemy)
{
	return;
}

void BossState_Attack::runState(Enemy* enemy, float dt)
{
	auto attackNumber = enemy->getAttackNumber();

	// Player�� ���� �Ÿ����� ���ٸ� Rush���·� ����.
	if (!isPlayerInAttackRange(enemy->getChasingRange(), enemy->getDistanceFromPlayer()))
	{
		enemy->changeState<BossState_Rush>();
	}
	// 3�� ������ �ߴٸ� ���� ȸ�� �ʱ�ȭ �� Strike ���·� ����.
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