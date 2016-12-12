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
	setStageOneTrigger(false);
	m_pEnemyVector.reserve(8);
	m_pMakeHandler[ENEMY_TYPE::CHOCO] = &EnemyManager::MakeChoco;
	m_pMakeHandler[ENEMY_TYPE::ATROCE] = &EnemyManager::MakeAtroce;
}

EnemyManager::~EnemyManager()
{
	int a;
}


Vector<Enemy*>* EnemyManager::getEnemyVector()
{
	return &m_pEnemyVector;
}

void EnemyManager::DeleteEnemy(void)
{
	auto enemyVector = getEnemyVector();

	for (int i = 0; i < enemyVector->size(); i++)
	{
		auto temp_enemy = enemyVector->at(i);
		if (temp_enemy->getHP() <= 0)
		{
			temp_enemy->getMapPointer()->removeChild(temp_enemy);

		}
	}
}

// Enemy타입과 첫 포지션을 받아 Enemy를 생성해주는 함수.
void EnemyManager::MakeEnemy(const ENEMY_TYPE enemyType, const Vec2 initPosition)
{
	// TODO :: 함수 포인터로 변환.
	Enemy* newEnemy;
	
	/*
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
	*/
	// Question :: 함수포인터 사용법.
	(this->*m_pMakeHandler[enemyType])(initPosition, newEnemy);

	newEnemy->setEnemyType(enemyType);
	newEnemy->setMapPointer(getMapPointer());
	m_pEnemyVector.pushBack(newEnemy);
	getMapPointer()->addChild(newEnemy);

	return;
}

bool EnemyManager::MakeChoco(const Vec2 initPosition, Enemy* newEnemy)
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Choco.plist");
	newEnemy = Enemy_Choco::create(initPosition);

	if (!newEnemy)
	{
		return false;
	}

	return true;
}

bool EnemyManager::MakeAtroce(const Vec2 initPosition, Enemy* newEnemy)
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Atroce.plist");
	newEnemy = Enemy_Atroce::create(initPosition);

	if (!newEnemy)
	{
		return false;
	}

	return true;
}



void EnemyManager::ProvidePlayerPosition(const Vec2 inputPlayerPosition)
{
	auto iter = m_pEnemyVector.begin();
	for (; iter != m_pEnemyVector.end(); ++iter)
	{
		(*iter)->setPlayerPosition(inputPlayerPosition);
	}

	return;
}

Enemy* EnemyManager::FindEnemyWithIdx(const int findIdx)
{
	return m_pEnemyVector.at(findIdx);
}

Vector<Enemy*>* EnemyManager::FindEnemyWithType(const ENEMY_TYPE findType)
{
	if (findType < ENEMY_TYPE::ENEMY_TYPE_NUM)
	{
		return nullptr;
	}

	auto returnVector = new Vector<Enemy*>;
	auto iter = m_pEnemyVector.begin();

	for (; iter != m_pEnemyVector.end(); ++iter)
	{
		if ((*iter)->getEnemyType() == findType)
		{
			returnVector->pushBack((*iter));
		}
	}
	
	return returnVector;
}


// TODO :: Function Stage 1 Setting 만들기. ( Choco 1,2가 죽으면 다른 몹 소환 )

void EnemyManager::StageOneSetting()
{
	// 구상중.
	setStageOneTrigger(true);
}
