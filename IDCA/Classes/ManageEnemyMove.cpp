#include "pch.h"
#include "ManageEnemyMove.h"
#include "ManageMap.h"
#include "TemporaryDefine.h"

bool ManageEnemyMove::init()
{
	if (!Node::init())
	{
		return false;
	}

	return true;
}

Vec2 ManageEnemyMove::update(Vec2 position, Vec2 unitVec, TMXTiledMap* map)
{
	m_pManageMap = ManageMap::create();

	auto movable = false;

	movable = m_pManageMap->checkWall(position + (unitVec), map);

	if (movable == true)
	{
		position += unitVec*TEMP_DEFINE::MONSTER_MOVE_SPEED;
	}

	return position;
}
