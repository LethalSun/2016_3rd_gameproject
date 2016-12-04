#pragma once

#include "EnemyState.h"

class AnimationMaker;
class Config;

class Enemy : public Node
{
public:
	virtual bool      init(Vec2);
	virtual void      update(float deltaTime) override;

	/* State */
	template<typename T_STATE>
	void              changeState();

	CC_SYNTHESIZE(EnemyState*, m_pState, State);
	CC_SYNTHESIZE(EnemyState*, m_pBeforeState, BeforeState);


	/* Member Variable */
	CC_SYNTHESIZE(float, m_SearchingRange, SearchingRange);
	CC_SYNTHESIZE(float, m_ChasingRange, ChasingRange);
	CC_SYNTHESIZE(float, m_AttackRange, AttackRange);
	CC_SYNTHESIZE(Point, m_Origin, Origin);
	CC_SYNTHESIZE(float, m_MoveSpeed, MoveSpeed);
	CC_SYNTHESIZE(bool , m_IsAttackedOnce, IsAttackedOnce);
	CC_SYNTHESIZE(bool , m_IsHited, IsHited);

	CC_SYNTHESIZE(Point, m_PlayerPosition, PlayerPosition)
	CC_SYNTHESIZE(float, m_DistanceFromPlayer, DistanceFromPlayer);
	CC_SYNTHESIZE(float, m_DistanceFromOrigin, DistanceFromOrigin);
	CC_SYNTHESIZE(Vec2 , m_UnitVec, UnitVec);


	/* Member Function */
	void				 move(const float deltaTime);
	void				 CalUnitVecToPlayer();
	void				 CalUnitVecToOrigin();
	void				 CalDistanceFromPlayer();
	void				 CalDistanceFromOrigin();
	void				 HitedMove(const float deltaTime);

	/* Create Function Re-define */
	static Enemy* create(Vec2 initPosition) {
		auto p = new Enemy();
		if (p->init(initPosition)) {
			p->autorelease();
			return p;
		}
		else {
			delete p;
			return nullptr;
		}
	}

	AnimationMaker*	  m_pAnimationMaker;
	Config*			  m_pConfig;
};


// State를 전환.
template <typename T_STATE>
void Enemy::changeState()
{
	// state가 존재한다면 종료.
	if (m_pState)
	{
		setBeforeState()->getState();
		getState()->endState(this);
		removeComponent(m_pState);
	}

	auto m_pState = T_STATE::create();
	setState(m_pState);
	getState()->startState(this);
	addComponent(m_pState);

	return;
}