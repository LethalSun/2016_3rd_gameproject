#include "pch.h"
#include "Enemy_Choco.h"
#include "EnemyState_Search.h"
#include "Config.h"


bool Enemy_Choco::init(Vec2 initPosition)
{
	if (!Enemy::init(initPosition))
	{
		return false;
	}

	// Config �̱��� Ŭ���� ȣ��.
	m_pConfig->getInstance();

	// ���� ������ ����.
	setSearchingRange	(m_pConfig->getChocoSearchingRange);
	setChasingRange		(m_pConfig->getChocoChasingRange);
	setAttackRange		(m_pConfig->getChocoAttackRange);
	setMoveSpeed		(m_pConfig->getChocoMoveSpeed);
	setIsAttackedOnce	(false);
	setIsHited			(false);

	setOrigin(Vec2(m_pConfig->getWinSizeWidth() * initPosition.x,
		m_pConfig->getWinSizeHeight() * initPosition.y));



	changeState<EnemyState_Search>();

	return true;
}