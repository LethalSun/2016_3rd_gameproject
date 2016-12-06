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

	scheduleUpdate();

	return true;
}


Vec2 ManageEnemyMove::update(Vec2 position, Vec2 unitVec, TMXTiledMap* map, const float dt)
{
	m_pManageMap = ManageMap::create();

	auto movable = false;

	movable = m_pManageMap->checkWall(position + (unitVec), map);

	if (movable == true)
	{
		position += unitVec * TEMP_DEFINE::MONSTER_MOVE_SPEED;
	}

	if (movable == false) CCLOG("ManageEnemyMove::update -> moveable is false!");
	if (movable == true) CCLOG("ManageEnemyMove::update -> moveable is true.");
	return position;
}


// update에서 TEMP_DEFINE::MONSTER_MOVE_SPEED를 사용하고 있는데, 각각 몬스터는 다른 MOVE_SPEED를 가지고 있잖아.
// 차라리 update의 인자를 하나 더 받아서, enemy에서 this를 넘겨주고, update에서는 enemy->getMoveSpeed를 하면 될 것 같음.
// 그리고 이 경우에는 deltaTime을 받지 않기 때문에 이상할 것 같은데..?