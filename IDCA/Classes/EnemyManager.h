#pragma once

// TODO :: EnemyManager에서 Enemy끼리의 거리를 검사해주기.
// 

class Enemy;
class Enemy_Choco;

class EnemyManager
{
public :
	static EnemyManager* getInstance();
	void deleteInstance();

	EnemyManager();

	~EnemyManager();

	/* Member Variable */
	CC_SYNTHESIZE(TMXTiledMap*, m_pMap, MapPointer);
	CC_SYNTHESIZE(bool, m_StageOneTrigger, StageOneTrigger);

	// 포인터는 원칙적으로 NULL 계산이 필요하기 때문에 NULL이 들어오지 않는 경우에 참조자 반환.
	Vector<Enemy*>&			getEnemyVector();
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

