#pragma once
#include "EnemyState.h"

/*
	BossState_Attack
	�ۼ��� : �̱ٿ�
	Boss�� ���� ���� ����� ���� ���� ����.
	�� �� ���� ��, Strike ���� ���·� ����.
	���� Player�� range�ȿ� ���ٸ� ������ ���ֺ��͸� ������ ���� ��, rush���·� ����.
*/


class BossState_Attack : public EnemyState
{
public :
	CREATE_FUNC(BossState_Attack);
	bool init() override
	{
		setName("BossState_Attack");
		return true;
	}

	void		startState(Enemy* enemy) override;
	void		runState(Enemy* enemy, float dt) override;
	void		endState(Enemy* enemy) override;

	const int	returnStateNumber() override;
};