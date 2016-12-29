#include "pch.h"
#include "SimpleAudioEngine.h"
#include "EnemyManager.h"
#include "Enemy_Choco.h"
#include "Enemy_Atroce.h"

const int STAGE_ONE_ENEMY_NUM = 20;
const char CHOCO_PLIST[] = "Choco.plist";
const char ATROCE_PLIST[] = "Atroce.plist";
const char TRIGGER_SOUND[] = "Sound/StageOne_triggerOn.wav";

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


// Manager�� ���� EnemyVector ��ȯ.
Vector<Enemy*>& EnemyManager::getEnemyVector()
{
	return m_pEnemyVector;
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
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(CHOCO_PLIST);
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
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(ATROCE_PLIST);
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

// Enemy�� �����͸� �־��ָ� Vector�� �ε����� ��ȯ���ִ� �Լ�. 
int EnemyManager::FindEnemyWithPointer(Enemy* enemyPointer)
{
	auto enemyVector = getEnemyVector();

	for (int i = 0; i < enemyVector.size(); i++)
	{
		auto temp_enemy = enemyVector.at(i);
		if (temp_enemy == enemyPointer)
		{
			return i;
		}
	}

	return -1;
}

// TODO :: Function Stage 1 Setting �����. ( Choco 1,2�� ������ �ٸ� �� ��ȯ )
void EnemyManager::StageOneSetting()
{
	// �ʱ� Choco Enemy ����.
	// TODO :: Choco Enemy �����ѹ� ���ֱ�.
	MakeEnemy(ENEMY_TYPE::CHOCO, Vec2(700.f, 650.f));
	MakeEnemy(ENEMY_TYPE::CHOCO, Vec2(800.f, 650.f));

	// �ʱ� Choco �� ������ �� ���� ������.
	m_pEnemyVector.at(0)->setIsEnemyPreemptive(false);
	m_pEnemyVector.at(1)->setIsEnemyPreemptive(false);

	return;
}

// StageOne�� Trigger�� �����Ǿ����� üũ���ִ� �Լ�.
// StageOne�� Update���� ȣ��.
void EnemyManager::StageOneTriggerCheck()
{
	// Trigger�� false�϶��� Ȯ��. (�ߺ� ȣ�� �Ұ�)
	if (!getStageOneTrigger() && IsStageOneChocoDied())
	{
		StageOneCreateAdditionalEnemies();
	}

	return;
}

// �ʱ⿡ �����ߴ� Choco �� ������ �׾����� Ȯ���ϰ� Trigger�� �ø��� �Լ�.
bool EnemyManager::IsStageOneChocoDied()
{
	if (m_pEnemyVector.empty())
	{
		setStageOneTrigger(true);
		return true;
	}

	return false;
}


// StageOne�� Ʈ���Ű� �ߵ��Ǹ� ������ Enemy���� �������ִ� �Լ�.
void EnemyManager::StageOneCreateAdditionalEnemies()
{
	// TODO :: ���� ��ġ ���� �ѹ� ���ֱ�.
	MakeEnemy(ENEMY_TYPE::ATROCE, Vec2(700.f, 650.f));
	MakeEnemy(ENEMY_TYPE::ATROCE, Vec2(750.f, 700.f));
	MakeEnemy(ENEMY_TYPE::ATROCE, Vec2(800.f, 850.f));
	MakeEnemy(ENEMY_TYPE::ATROCE, Vec2(900.f, 900.f));

	// Sound ���
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(TRIGGER_SOUND, false);

	return;
}

// �� Update���� Enemy�� �׾����� Ȯ���� �ϰ� release�� �������ش�.
void EnemyManager::DieCheck()
{
	for (int i = 0; i < m_pEnemyVector.size(); ++i)
	{
		auto tmpEnemy = m_pEnemyVector.at(i);
		if (tmpEnemy->getHP() <= 0)
		{
			m_pEnemyVector.erase(i);
			getMapPointer()->removeChild(tmpEnemy);
		}
	}

	return;
}