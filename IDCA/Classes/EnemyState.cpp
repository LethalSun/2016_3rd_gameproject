#include "pch.h"
#include "EnemyState.h"

// �÷��̾ enemy�� Chasing_Range �ȿ� �ִٸ� true�� ��ȯ�ϴ� �Լ�.
bool EnemyState::isPlayerInChasingRange(float chasingRange, float distance)
{
	if (distance < chasingRange)
	{
		return true;
	}

	return false;
}

// �÷��̾ enemy�� Attack_Range�ȿ� �ִٸ� true�� ��ȯ�ϴ� �Լ�.
bool EnemyState::isPlayerInAttackRange(float attackRange, float distance)
{
	if (distance < attackRange)
	{
		return true;
	}

	return false;
}

// �÷��̾ enemy�� SEARCHING_RANGE�ȿ� �ִٸ� true�� ��ȯ�ϴ� �Լ�.
bool EnemyState::isPlayerInSearchRange(float searchRange, float distance)
{
	if (distance < searchRange)
	{
		return true;
	}

	return false;
}
