#include "pch.h"
#include "Enemy.h"
#include "EnemyManager.h"
#include "SimpleAudioEngine.h"
#include "Enemy_AncientTree.h"
#include "BossState_Attack.h"
#include "BossState_Strike.h"
#include "BossState_Rush.h"

/*
	BossState_Attack
	�ۼ��� : �̱ٿ�
	Boss�� ������ �ϴ� ����.
	Boss������ ���� Ƚ���� ���� ���� Strike ���·� ����.
	���� player�� ���� ���� �ٱ��̶�� Rush ���·� ����.
	������ �ϴ� ���
		- MakeTentacle�Լ��� ���� �켱 �Ѹ��� ��ȯ ( TODO :: Vector�� ���� )
*/

const float AttackFrequency = 1.4f;

void BossState_Attack::startState(Enemy* enemy)
{
	return;
}

void BossState_Attack::runState(Enemy* enemy, float dt)
{
	auto attackNumber = enemy->getAttackNumber();
	m_AccumulateTime += dt;

	// Player�� ���� �Ÿ����� ���ٸ� Rush���·� ����.
	if (!isPlayerInAttackRange(enemy->getChasingRange(), enemy->getDistanceFromPlayer()))
	{
		enemy->changeState<BossState_Rush>();
	}
	// Player�� 3�� ������ ���� �ʾҴٸ�.
	else if (attackNumber != 3)
	{
		// ������ AttackFrequency�� ���� �޶�����.
		// TODO :: AttackFrequency�� Enemy���ο��� �����ų� Define���� �ű��.
		if (m_AccumulateTime > AttackFrequency)
		{
			// Tentacle�� ������� ��, attackNumber�� ����. 
			enemy->MakeTentacle();
			enemy->setAttackNumber(++attackNumber);
			m_AccumulateTime = 0.f;
		}
	}
	// 3�� ������ �ߴٸ� ���� ȸ�� �ʱ�ȭ �� Strike ���·� ����.
	else 
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

