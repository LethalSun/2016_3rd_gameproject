#pragma once

class Enemy;

// Enemy의 State를 관리하기 위해 만든 순수 가상 클래스. 
class EnemyState : public Component
{
public:
	// State가 시작하는 함수.
	virtual void startState(Enemy* enemy) = 0;

	// 매 프레임 호출될 함수.
	virtual void runState(Enemy* enemy, float dt) = 0;

	// State를 종료 시킬 함수.
	virtual void endState(Enemy* enemy) = 0;


	/* Calculate Functions */
	bool	   	 isPlayerInChasingRange(float, float);
	bool	     isPlayerInAttackRange(float, float);
	bool		 isPlayerInSearchRange(float, float);
};
