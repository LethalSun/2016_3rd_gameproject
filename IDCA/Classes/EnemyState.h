#pragma once

class Enemy;

// Enemy�� State�� �����ϱ� ���� ���� ���� ���� Ŭ����. 
class EnemyState : public Component
{
public:
	// State�� �����ϴ� �Լ�.
	virtual void startState(Enemy* enemy) = 0;

	// �� ������ ȣ��� �Լ�.
	virtual void runState(Enemy* enemy, float dt) = 0;

	// State�� ���� ��ų �Լ�.
	virtual void endState(Enemy* enemy) = 0;


	/* Calculate Functions */
	bool	   	 isPlayerInChasingRange(const float, const float);
	bool	     isPlayerInAttackRange(const float, const float);
	bool		 isPlayerInSearchRange(const float, const float);
	virtual const int returnStateNumber() = 0;
};
