#include "pch.h"
#include "ManageEnemyMove.h"
#include "ManageMap.h"
#include "TemporaryDefine.h"
#include "Enemy.h"
bool ManageEnemyMove::init()
{
	if (!Node::init())
	{
		return false;
	}

	scheduleUpdate();

	return true;
}


Vec2 ManageEnemyMove::update(Vec2 position, Vec2 unitVec, TMXTiledMap* map, const float dt,Enemy* enemy)
{
	m_pManageMap = ManageMap::create();

	auto movable = false;

	movable = m_pManageMap->checkWall(position + (unitVec)*5, map);

	if (movable == true)
	{
		position += unitVec * enemy->getMoveSpeed();
	}

	if (movable == false) CCLOG("ManageEnemyMove::update -> moveable is false!");
	if (movable == true) CCLOG("ManageEnemyMove::update -> moveable is true.");
	return position;
}


// update���� TEMP_DEFINE::MONSTER_MOVE_SPEED�� ����ϰ� �ִµ�, ���� ���ʹ� �ٸ� MOVE_SPEED�� ������ ���ݾ�.
// ���� update�� ���ڸ� �ϳ� �� �޾Ƽ�, enemy���� this�� �Ѱ��ְ�, update������ enemy->getMoveSpeed�� �ϸ� �� �� ����.
// �׸��� �� ��쿡�� deltaTime�� ���� �ʱ� ������ �̻��� �� ������..?