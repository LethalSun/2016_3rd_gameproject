#include "pch.h"
#include "EnemyManager.h"
#include "Enemy_Choco.h"
#include "Enemy_Atroce.h"

const int STAGE_ONE_ENEMY_NUM = 20;

// EnemyManager ������.
// EnemyVector�� Stage 1�� ���� Enemy�� ������ŭ ������ ����, ���� �Լ� �����͸� �ڵ鷯�� ����ش�. 
EnemyManager::EnemyManager()
{
	setStageOneTrigger(false);
	m_pEnemyVector.reserve(STAGE_ONE_ENEMY_NUM);
	m_pMakeHandler[ENEMY_TYPE::CHOCO] = &EnemyManager::MakeChoco;
	m_pMakeHandler[ENEMY_TYPE::ATROCE] = &EnemyManager::MakeAtroce;
}

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
	CCLOG("Delete EnemyManager!");
	return;
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
	// �Լ������� m_pMakeHandler���.
	Enemy* newEnemy = (this->*m_pMakeHandler[enemyType])(initPosition);

	// Enemy ���� ó�� �κ�.
	newEnemy->setEnemyType(enemyType);
	newEnemy->setMapPointer(getMapPointer());
	m_pEnemyVector.pushBack(newEnemy);
	getMapPointer()->addChild(newEnemy);

	return;
}

// Choco�� ����� �Լ�.
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

// Atroce�� ����� �Լ�.
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


// Vector���� ��� Enemy���� Player Position�� �Ѱ��ִ� �Լ�.
void EnemyManager::ProvidePlayerPosition(const Vec2 inputPlayerPosition)
{
	auto iter = m_pEnemyVector.begin();
	for (; iter != m_pEnemyVector.end(); ++iter)
	{
		(*iter)->setPlayerPosition(inputPlayerPosition);
	}

	return;
}

// Vector��ȣ�� ������ �ش��ϴ� Enemy�� �����͸� ��ȯ�� �ִ� �Լ�.
Enemy* EnemyManager::FindEnemyWithIdx(const int findIdx)
{
	return m_pEnemyVector.at(findIdx);
}

// Enemy Type�� ������ �ش��ϴ� Enemy���� ���� Vector�� ���·� ��ȯ�� �ִ� �Լ�.
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
