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
	// 함수포인터 m_pMakeHandler사용.
	Enemy* newEnemy = (this->*m_pMakeHandler[enemyType])(initPosition);

	// Enemy 공동 처리 부분.
	newEnemy->setEnemyType(enemyType);
	newEnemy->setMapPointer(getMapPointer());
	m_pEnemyVector.pushBack(newEnemy);
	getMapPointer()->addChild(newEnemy);

	return;
}

// Choco를 만드는 함수.
Enemy* EnemyManager::MakeChoco(const Vec2 initPosition)
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Choco.plist");
	Enemy* newEnemy = Enemy_Choco::create(initPosition);

	if (!newEnemy)
	{
		return nullptr;
	}

	return newEnemy;
}

// Atroce를 만드는 함수.
Enemy* EnemyManager::MakeAtroce(const Vec2 initPosition)
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Atroce.plist");
	Enemy* newEnemy = Enemy_Atroce::create(initPosition);

	if (!newEnemy)
	{
		return nullptr;
	}

	return newEnemy;
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
