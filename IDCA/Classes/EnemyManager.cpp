#include "pch.h"
#include "EnemyManager.h"
#include "Enemy_Choco.h"
#include "Enemy_Atroce.h"

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


Vector<Enemy*>* EnemyManager::getEnemyVector()
{
	return &m_pEnemyVector;
}

// Enemy타입과 첫 포지션을 받아 Enemy를 생성해주는 함수.
void EnemyManager::MakeEnemy(const ENEMY_TYPE enemyType, const Vec2 initPosition)
{
	// TODO :: 함수 포인터로 변환.
	Enemy* newEnemy;
	if (enemyType == ENEMY_TYPE::CHOCO)
	{
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Choco.plist");
		newEnemy = Enemy_Choco::create(initPosition);
	}
	else if (enemyType == ENEMY_TYPE::ATROCE)
	{
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Atroce.plist");
		newEnemy = Enemy_Atroce::create(initPosition);
	}

	newEnemy->setEnemyType(enemyType);
	newEnemy->setMapPointer(getMapPointer());
	m_pEnemyVector.pushBack(newEnemy);
	getMapPointer()->addChild(newEnemy);

	return;
}

void EnemyManager::ProvidePlayerPosition(const Vec2 inputPlayerPosition)
{
	auto iter = m_pEnemyVector.begin();
	for (; iter != m_pEnemyVector.end(); ++iter)
	{
		(*iter)->setPlayerPosition(inputPlayerPosition);
	}

	/*
	for (int i = 0; i < m_pEnemyVector.size(); ++i)
	{
		m_pEnemyVector.at(i)->setPlayerPosition(inputPlayerPosition);
	}
	*/

	return;
}

// TODO :: Function Stage 1 Setting 만들기. ( Choco 1,2가 죽으면 다른 몹 소환 )