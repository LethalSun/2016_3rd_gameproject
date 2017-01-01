#include "pch.h"
#include "Enemy_AncientTree.h"
#include "EnemyState_Search.h"
#include "AnimationMaker.h"

const float AncientTree_SearchingRange = 1500.f;
const float AncientTree_ChansingRange = 1500.f;
const float AncientTree_AttackRange = 1500.f;
const float AncientTree_MoveSpeed = 2.f;
const float AncientTree_StiffTime = 0.7f;

const char AncientTree_Name[] = "AncientTree";
const char AncientTree_Extension[] = ".png";

bool Enemy_AncientTree::init(const Vec2 initPosition)
{
	if (!Enemy::init(initPosition))
	{
		return false;
	}

	setSearchingRange(AncientTree_SearchingRange);
	setChasingRange(AncientTree_ChansingRange);
	setAttackRange(AncientTree_AttackRange);
	setMaxHP(ANCIENT_TREE_MAX_HP);
	setHP(ANCIENT_TREE_MAX_HP);
	setDamage(ANCIENT_TREE_DAMAGE);

	auto BodyRange = Vec2(ANCIENT_TREE_BODY_RANGE_X, ANCIENT_TREE_BODY_RANGE_Y);
	setBodyRangeForCollide(BodyRange);

	setIsAttackedOnce(false);
	setIsEnemyPreemptive(true);
	setAttackNumber(0);

	// AnimationMaker ¼¼ÆÃ.
	m_pAnimationMaker = AnimationMaker::create(AncientTree_Name, AncientTree_Extension);
	addChild(m_pAnimationMaker);
	m_pAnimationMaker->SetAnimationStop();
	m_pAnimationMaker->AddAnimation(getDirection());

	changeState<EnemyState_Search>();

	return true;
}