#pragma once


class Enemy;

class EnemyManager 
{
public :
	static EnemyManager* getInstance();
	void deleteInstance();

	EnemyManager();


	// TODO :: FIND함수 제공해주기. 벡터 자체를 주지 말고, 원하는 에너미 객체만 던져주기.
	// FIND(idx) 뭐 이런식으로 하던가, ENEMY의 TAG로 찾던가.
	// 두 가지 함수 제공해주기.
	/* Member Variable */
	std::vector<Enemy*>		m_pEnemyVector;
	
	/* Member Function */
	void MakeEnemy(ENEMY::ENEMY_TYPE, Vec2);

private :
	static EnemyManager* _instance;

};

