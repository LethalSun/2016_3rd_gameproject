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

// EnemyŸ�԰� ù �������� �޾� Enemy�� �������ִ� �Լ�.
void EnemyManager::MakeEnemy(const ENEMY_TYPE enemyType, const Vec2 initPosition)
{
	// TODO :: �Լ� �����ͷ� ��ȯ.
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
	// Question :: �Լ������� ����.
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


// TODO :: Function Stage 1 Setting �����. ( Choco 1,2�� ������ �ٸ� �� ��ȯ )

void EnemyManager::StageOneSetting()
{
	// ������.
	setStageOneTrigger(true);
}
