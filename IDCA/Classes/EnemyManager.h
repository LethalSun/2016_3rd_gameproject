#pragma once


class Enemy;
class Enemy_Choco;

class EnemyManager
{
public :
	static EnemyManager* getInstance();
	void deleteInstance();

	EnemyManager();

	/* Member Variable */
	CC_SYNTHESIZE(TMXTiledMap*, m_pMap, MapPointer);
	CC_SYNTHESIZE(bool, m_StageOneTrigger, StageOneTrigger);
	CC_SYNTHESIZE(int, m_DiedEnemyNum, DiedEnemyNum);
	CC_SYNTHESIZE(int, m_SoundPlayNum, SoundPlayNum);

	// 포인터는 원칙적으로 NULL 계산이 필요하기 때문에 NULL이 들어오지 않는 경우에 참조자 반환.
	Vector<Enemy*>&			getEnemyVector();
	Vector<Enemy*>&			getDeleteEenemyVector();
	Enemy*(EnemyManager::*  m_pMakeHandler[ENEMY_TYPE::ENEMY_TYPE_NUM])(const Vec2);
	
	/* Member Function */
	void					MakeEnemy(const ENEMY_TYPE, const Vec2);
	void					MakeEnemy(const ENEMY_TYPE, const Vec2, const bool);
	void					ProvidePlayerPosition(const Vec2);
	Enemy*					FindEnemyWithIdx(const int);
	Vector<Enemy*>*			FindEnemyWithType(const ENEMY_TYPE);
	int 					FindEnemyWithPointer(Enemy*);

	void					StageOneSetting();
	void					StageOneTriggerCheck();
	bool					IsStageOneChocoDied();
	void					StageOneCreateAdditionalEnemies();
	void					DieCheck();

	Enemy*					MakeChoco(const Vec2);
	Enemy*					MakeAtroce(const Vec2);

private :
	static EnemyManager*	_instance;
	Vector<Enemy*>			m_pEnemyVector;
	Vector<Enemy*>			m_DeleteEnemyVector;
};

