#include "pch.h"
#include "EnemyManager.h"
#include "Enemy_Choco.h"
#include "Enemy_Atroce.h"

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
	m_pEnemyVector.reserve(8);
}


Vector<Enemy*>* EnemyManager::getEnemyVector()
{
	return &m_pEnemyVector;
}

// EnemyŸ�԰� ù �������� �޾� Enemy�� �������ִ� �Լ�.
void EnemyManager::MakeEnemy(const ENEMY_TYPE enemyType, const Vec2 initPosition)
{

	if (enemyType == ENEMY_TYPE::CHOCO)
	{
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Choco.plist");
		auto* newEnemy = Enemy_Choco::create(initPosition);
		newEnemy->setEnemyType(ENEMY_TYPE::CHOCO);
		newEnemy->setMapPointer(getMapPointer());
		m_pEnemyVector.pushBack(newEnemy);
		getMapPointer()->addChild(newEnemy);
	}
	else if (enemyType == ENEMY_TYPE::ATROCE)
	{
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Atroce.plist");
		auto* newEnemy = Enemy_Atroce::create(initPosition);
		newEnemy->setEnemyType(ENEMY_TYPE::ATROCE);
		newEnemy->setMapPointer(getMapPointer());
		m_pEnemyVector.pushBack(newEnemy);
		getMapPointer()->addChild(newEnemy);
	}


	return;
}

void EnemyManager::ProvidePlayerPosition(const Vec2 inputPlayerPosition)
{
	for (int i = 0; i < m_pEnemyVector.size(); ++i)
	{
		m_pEnemyVector.at(i)->setPlayerPosition(inputPlayerPosition);
	}

	return;
}
