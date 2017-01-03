#pragma once
class ManageMap;
class Enemy;
class EnemyManager;



class ManageEnemyMove : public Component
{
public:

	CREATE_FUNC(ManageEnemyMove);



	virtual bool init() override;

	Vec2 update(Vec2 position, Vec2 unitvec, TMXTiledMap * map, const float,Enemy* );
	ManageMap* m_pManageMap;
	Vector<Enemy*>* enemyVector;

private:

	EnemyManager* m_EnemyManager;
};

