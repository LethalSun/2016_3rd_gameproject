#include "pch.h"
#include "EnemyState.h"

// �÷��̾ enemy�� Chasing_Range �ȿ� �ִٸ� true�� ��ȯ�ϴ� �Լ�.
bool EnemyState::isPlayerInChasingRange(const float chasingRange, const float distance)
{
	if (distance < chasingRange)
	{
		return true;
	}

	return false;
}

// �÷��̾ enemy�� Attack_Range�ȿ� �ִٸ� true�� ��ȯ�ϴ� �Լ�.
bool EnemyState::isPlayerInAttackRange(const float attackRange, const float distance)
{
	if (distance < attackRange)
	{
		return true;
	}

	return false;
}

// �÷��̾ enemy�� SEARCHING_RANGE�ȿ� �ִٸ� true�� ��ȯ�ϴ� �Լ�.
bool EnemyState::isPlayerInSearchRange(const float searchRange, const float distance)
{
	if (distance < searchRange)
	{
		return true;
	}

	return false;
}
