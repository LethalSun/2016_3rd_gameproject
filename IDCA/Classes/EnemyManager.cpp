#include "pch.h"
#include "EnemyManager.h"
#include "Enemy_Choco.h"

EnemyManager* EnemyManager::_instance = nullptr;

// EnemyManager �̱��� ����.
EnemyManager* EnemyManager::getInstance()
{
	if (!_instance)
	{
		_instance = new EnemyManager();
	}
	return _instance;
}


// �̱����� �����ִ� �Լ�.
void EnemyManager::deleteInstance()
{
	// TODO :: LOG�� ����Ͽ� ��¥ ȣ���ϴ��� ���ϴ��� Ȯ�����ֱ�.
	delete _instance;
	_instance = nullptr;
	return;
}

// TODO :: �����ڴ� �� ���� �ű��.
// �ʱ�ȭ �Լ�. 
EnemyManager::EnemyManager()
{
	m_pEnemyVector.reserve(ENEMY::ENEMY_MAX_NUM);
}


// EnemyŸ�԰� ù �������� �޾� Enemy�� �������ִ� �Լ�.
void EnemyManager::MakeEnemy(ENEMY::ENEMY_TYPE enemyType, Vec2 initPosition)
{
	if (enemyType == ENEMY::ENEMY_TYPE::Choco)
	{
		auto newEnemy = Enemy_Choco::create(initPosition);
		m_pEnemyVector.push_back(newEnemy);
	}
}
