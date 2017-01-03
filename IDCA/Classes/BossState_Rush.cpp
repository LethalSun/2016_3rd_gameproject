#include "pch.h"
#include "Enemy.h"
#include "BossState_Rush.h"
#include "BossState_Attack.h"
#include "EnemyState_Search.h"
#include "ManageEnemyMove.h"


// 상태 시작시, 유닛벡터 계산과 애니메이션을 위한 Distance계산을 해준다.
void BossState_Rush::startState(Enemy* enemy)
{
	m_AcculmulateTime = 0.f;
	enemy->CalUnitVecToPlayer();
	enemy->TranslateUnitVec(enemy->getUnitVecToPlayer());
	enemy->CalDirection(enemy->getTranslatedUnitVec());
	return;
}

// Rush타임만큼 달려간 뒤, 서칭 상태로 변환.
void BossState_Rush::runState(Enemy* enemy, float dt)
{
	m_AcculmulateTime += dt;

	if (m_AcculmulateTime > ANCIENT_TREE_RUSH_TIME)
	{
		enemy->changeState<EnemyState_Search>();
	}
	else 
	{
		auto position = enemy->m_pManageEnemyMove->update(enemy->getPosition(), enemy->getUnitVecToPlayer(), enemy->getMapPointer(), dt, enemy);
		enemy->setPosition(position);
	}
	return;
}

void BossState_Rush::endState(Enemy* enemy)
{
	return;
}

const int BossState_Rush::returnStateNumber()
{
	return ENEMY_STATE_TYPE::BOSS_RUSH;
}