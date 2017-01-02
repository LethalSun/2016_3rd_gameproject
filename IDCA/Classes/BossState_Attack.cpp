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
	작성자 : 이근원
	Boss가 공격을 하는 상태.
	Boss내부의 공격 횟수가 가득 차면 Strike 상태로 돌입.
	만약 player가 공격 범위 바깥이라면 Rush 상태로 돌입.
	공격을 하는 경우
		- MakeTentacle함수를 통해 우선 뿌리를 소환 ( TODO :: Vector로 관리 )
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

	// Player가 공격 거리내에 없다면 Rush상태로 변경.
	if (!isPlayerInAttackRange(enemy->getChasingRange(), enemy->getDistanceFromPlayer()))
	{
		enemy->changeState<BossState_Rush>();
	}
	// Player가 3번 공격을 하지 않았다면.
	else if (attackNumber != 3)
	{
		// 공격은 AttackFrequency에 따라서 달라진다.
		// TODO :: AttackFrequency를 Enemy내부에서 얻어오거나 Define으로 옮기기.
		if (m_AccumulateTime > AttackFrequency)
		{
			// Tentacle을 만들어준 뒤, attackNumber를 증가. 
			enemy->MakeTentacle();
			enemy->setAttackNumber(++attackNumber);
			m_AccumulateTime = 0.f;
		}
	}
	// 3번 공격을 했다면 공격 회수 초기화 후 Strike 상태로 변경.
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

