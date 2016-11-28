#pragma once


class Enemy;

class EnemyManager 
{
public :
	static EnemyManager* getInstance();
	void deleteInstance();

	EnemyManager();


	// TODO :: FIND�Լ� �������ֱ�. ���� ��ü�� ���� ����, ���ϴ� ���ʹ� ��ü�� �����ֱ�.
	// FIND(idx) �� �̷������� �ϴ���, ENEMY�� TAG�� ã����.
	// �� ���� �Լ� �������ֱ�.
	/* Member Variable */
	std::vector<Enemy*>		m_pEnemyVector;
	
	/* Member Function */
	void MakeEnemy(ENEMY::ENEMY_TYPE, Vec2);

private :
	static EnemyManager* _instance;

};

