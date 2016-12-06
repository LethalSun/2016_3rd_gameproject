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
	// TODO :: LOG를 사용하여 진짜 호출하는지 안하는지 확인해주기.
	delete _instance;
	_instance = nullptr;
	return;
}

// TODO :: 생성자는 맨 위로 옮기기.
// 초기화 함수. 
EnemyManager::EnemyManager()
{
	m_pEnemyVector.reserve(8);
}


// Enemy타입과 첫 포지션을 받아 Enemy를 생성해주는 함수.
void EnemyManager::MakeEnemy(const ENEMY_TYPE enemyType, const Vec2 initPosition)
{
	if (enemyType == ENEMY_TYPE::CHOCO)
	{
		auto newEnemy = Enemy_Choco::create(initPosition);
		m_pEnemyVector.push_back(newEnemy);
		
	}
}
