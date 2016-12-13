#pragma once


class Enemy;
class Enemy_Choco;

class EnemyManager
{
public :
	static EnemyManager* getInstance();
	void deleteInstance();

	EnemyManager();

	~EnemyManager();

	// TODO :: FIND함수 제공해주기. 벡터 자체를 주지 말고, 원하는 에너미 객체만 던져주기.
	// FIND(idx) 뭐 이런식으로 하던가, ENEMY의 TAG로 찾던가.
	// 두 가지 함수 제공해주기.
	/* Member Variable */
	CC_SYNTHESIZE(TMXTiledMap*, m_pMap, MapPointer);
	CC_SYNTHESIZE(bool, m_StageOneTrigger, StageOneTrigger);
	Vector<Enemy*>*			getEnemyVector();
	Enemy*(EnemyManager::*m_pMakeHandler[ENEMY_TYPE::ENEMY_TYPE_NUM])(const Vec2);
	void					DeleteEnemy();
	
	/* Member Function */
	void					MakeEnemy(const ENEMY_TYPE, const Vec2);
	void					ProvidePlayerPosition(const Vec2);
	Enemy*					FindEnemyWithIdx(const int);
	Vector<Enemy*>*			FindEnemyWithType(const ENEMY_TYPE);
	void					StageOneSetting();

	Enemy*					MakeChoco(const Vec2);
	Enemy*					MakeAtroce(const Vec2);

private :
	static EnemyManager*	_instance;
	Vector<Enemy*>			m_pEnemyVector;
};

