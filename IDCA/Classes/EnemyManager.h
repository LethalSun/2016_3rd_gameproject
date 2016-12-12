#pragma once


class Enemy;
class Enemy_Choco;

class EnemyManager : public Node
{
public :
	static EnemyManager* getInstance();
	void deleteInstance();

	EnemyManager();

	/* Member Variable */
	CC_SYNTHESIZE(TMXTiledMap*, m_pMap, MapPointer);
	CC_SYNTHESIZE(bool, m_StageOneTrigger, StageOneTrigger);
	Vector<Enemy*>*			getEnemyVector();
	bool(EnemyManager::*m_pMakeHandler[ENEMY_TYPE::ENEMY_TYPE_NUM])(const Vec2, Enemy*);
	
	/* Member Function */
	void					MakeEnemy(const ENEMY_TYPE, const Vec2);
	void					ProvidePlayerPosition(const Vec2);
	Enemy*					FindEnemyWithIdx(const int);
	Vector<Enemy*>*			FindEnemyWithType(const ENEMY_TYPE);
	void					StageOneSetting();

	bool					MakeChoco(const Vec2, Enemy*);
	bool					MakeAtroce(const Vec2, Enemy*);

private :
	static EnemyManager*	_instance;
	Vector<Enemy*>			m_pEnemyVector;
};

