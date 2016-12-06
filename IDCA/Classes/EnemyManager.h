#pragma once


class Enemy;
class Enemy_Choco;

class EnemyManager : public Node
{
public :
	static EnemyManager* getInstance();
	void deleteInstance();

	EnemyManager();


	// TODO :: FIND�Լ� �������ֱ�. ���� ��ü�� ���� ����, ���ϴ� ���ʹ� ��ü�� �����ֱ�.
	// FIND(idx) �� �̷������� �ϴ���, ENEMY�� TAG�� ã����.
	// �� ���� �Լ� �������ֱ�.
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

