#pragma once
class ManageMap;
class Enemy;
class EnemyManager;

class ManageEnemyMove : public Component
{
public:

	CREATE_FUNC(ManageEnemyMove);
	ManageEnemyMove() = default;
	~ManageEnemyMove() = default;



	bool init();

	//void SetEnemyManager(EnemyManager * ptr);

	Vec2 update(Vec2 position, Vec2 unitvec, TMXTiledMap * map, const float,Enemy* );
	Vector<Enemy*>* enemyVector;

private:
	ManageMap* m_pManageMap;
	EnemyManager* m_EnemyManager;
};

