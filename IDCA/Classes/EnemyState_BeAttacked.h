#pragma once
#include "EnemyState.h"

/*
	EnemyState_BeAttacked
	�ۼ��� : �̱ٿ�
	������ ����Ǵ� State.
	
	Enemy������ �����ð�(StiffTime)���� �����Ǿ��ٰ�, Search ���·� �����Ѵ�.
	State���ο��� ������ �Ǵ� Action�� �и��� Action�� ó���Ѵ�.
*/

class EnemyState_BeAttacked : public EnemyState
{
public:
	CREATE_FUNC(EnemyState_BeAttacked);
	bool		init() override
	{
		setName("EnemyState_BeAttacked");
		return true;
	}

	float		m_AccumulateTime = 0.f;

	void		startState(Enemy* enemy) override;
	void		runState(Enemy* enemy, const float deltaTime) override;
	void		endState(Enemy* enemy) override;
	const int   returnStateNumber() override;

	EaseElasticInOut* m_pEasePushedAction;
	bool        m_Pushable;
	void		MakePushAction(Enemy*);
	void		MakeRedAction(Enemy*);
};