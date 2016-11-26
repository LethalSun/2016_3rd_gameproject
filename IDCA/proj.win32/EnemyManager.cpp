#include "pch.h"
#include "EnemyManager.h"

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
	delete _instance;
	_instance = nullptr;
	return;
}

// �ʱ�ȭ �Լ�.
EnemyManager::EnemyManager()
{
	m_pEnemyVector.reserve(ENEMY::ENEMY_MAX_NUM);
}


// EnemyŸ�԰� ù �������� �޾� Enemy�� �������ִ� �Լ�.
void EnemyManager::MakeEnemy(ENEMY::ENEMY_TYPE enemyType, Vec2 initPosition)
{
	void(*handler[ENEMY::ENEMY_TYPE::EnemyTypeNum])(ENEMY::ENEMY_TYPE enemyType, Vec2 initPosition) = {};
}
