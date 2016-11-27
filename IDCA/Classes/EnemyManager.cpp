#include "pch.h"
#include "EnemyManager.h"
#include "Enemy_Choco.h"

EnemyManager* EnemyManager::_instance = nullptr;

// EnemyManager 싱글톤 구현.
EnemyManager* EnemyManager::getInstance()
{
	if (!_instance)
	{
		_instance = new EnemyManager();
	}
	return _instance;
}


// 싱글톤을 지워주는 함수.
void EnemyManager::deleteInstance()
{
	delete _instance;
	_instance = nullptr;
	return;
}

// 초기화 함수.
EnemyManager::EnemyManager()
{
	m_pEnemyVector.reserve(ENEMY::ENEMY_MAX_NUM);
}


// Enemy타입과 첫 포지션을 받아 Enemy를 생성해주는 함수.
void EnemyManager::MakeEnemy(ENEMY::ENEMY_TYPE enemyType, Vec2 initPosition)
{
	if (enemyType == ENEMY::ENEMY_TYPE::Choco)
	{
		auto newEnemy = Enemy_Choco::create(initPosition);
		m_pEnemyVector.push_back(newEnemy);
	}
}
