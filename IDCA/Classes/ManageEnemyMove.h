#pragma once
class ManageMap;
class Enemy;

class ManageEnemyMove : public Node
{
public:

	CREATE_FUNC(ManageEnemyMove);
	ManageEnemyMove() = default;
	~ManageEnemyMove() = default;



	bool init();

	Vec2 update(Vec2 position, Vec2 unitvec, TMXTiledMap * map, const float,Enemy* );


private:
	ManageMap* m_pManageMap;
};

