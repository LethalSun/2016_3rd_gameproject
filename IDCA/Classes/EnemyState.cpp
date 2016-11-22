#include "pch.h"
#include "EnemyState.h"

// 플레이어가 enemy의 Chasing_Range 안에 있다면 true를 반환하는 함수.
bool EnemyState::isPlayerInChasingRange(const float chasingRange, const float distance)
{
	if (distance < chasingRange)
	{
		return true;
	}

	return false;
}

// 플레이어가 enemy의 Attack_Range안에 있다면 true를 반환하는 함수.
bool EnemyState::isPlayerInAttackRange(const float attackRange, const float distance)
{
	if (distance < attackRange)
	{
		return true;
	}

	return false;
}

// 플레이어가 enemy의 SEARCHING_RANGE안에 있다면 true를 반환하는 함수.
bool EnemyState::isPlayerInSearchRange(const float searchRange, const float distance)
{
	if (distance < searchRange)
	{
		return true;
	}

	return false;
}
