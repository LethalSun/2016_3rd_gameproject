#pragma once


class Enemy;
class Enemy_Choco;

class EnemyManager : public Node
{
public :
	static EnemyManager* getInstance();
	void deleteInstance();

	EnemyManager();


	// TODO :: FIND함수 제공해주기. 벡터 자체를 주지 말고, 원하는 에너미 객체만 던져주기.
	// FIND(idx) 뭐 이런식으로 하던가, ENEMY의 TAG로 찾던가.
	// 두 가지 함수 제공해주기.
	/* Member Variable */
	CC_SYNTHESIZE(TMXTiledMap*, m_pMap, MapPointer);
	Vector<Enemy*>* getEnemyVector();
	
	/* Member Function */
	void MakeEnemy(const ENEMY_TYPE, const Vec2);
	void ProvidePlayerPosition(const Vec2);
	

private :
	static EnemyManager* _instance;
	Vector<Enemy*> m_pEnemyVector;
};

