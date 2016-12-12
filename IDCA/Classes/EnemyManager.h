#pragma once


class Enemy;
class Enemy_Choco;

class EnemyManager
{
public :
	static EnemyManager* getInstance();
	void deleteInstance();
	Vector<Enemy*> m_pEnemyVector;

	EnemyManager();

	~EnemyManager();

	// TODO :: FIND�Լ� �������ֱ�. ���� ��ü�� ���� ����, ���ϴ� ���ʹ� ��ü�� �����ֱ�.
	// FIND(idx) �� �̷������� �ϴ���, ENEMY�� TAG�� ã����.
	// �� ���� �Լ� �������ֱ�.
	/* Member Variable */
	CC_SYNTHESIZE(TMXTiledMap*, m_pMap, MapPointer);
	Vector<Enemy*>* getEnemyVector();

	void DeleteEnemy(void);
	
	/* Member Function */
	void MakeEnemy(const ENEMY_TYPE, const Vec2);
	void ProvidePlayerPosition(const Vec2);
	

private :
	static EnemyManager* _instance;
	
};

