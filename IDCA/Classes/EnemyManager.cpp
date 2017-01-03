#include "pch.h"
#include "SimpleAudioEngine.h"
#include "AudioEngine.h"
#include "EnemyState.h"
#include "EnemyManager.h"
#include "Enemy_Choco.h"
#include "Enemy_Atroce.h"
#include "Enemy_AncientTree.h"
#include "EnemyState_Dead.h"

const int STAGE_ONE_ENEMY_NUM = 20;
const char CHOCO_PLIST[] = "Choco.plist";
const char ATROCE_PLIST[] = "Atroce.plist";
const char ANCIENT_TREE_PLIST[] = "AncientTree.plist";
const char TRIGGER_SOUND[] = "Sound/StageOne_triggerOn.wav";

// EnemyManager ������.
// EnemyVector�� Stage 1�� ���� Enemy�� ������ŭ ������ ����, ���� �Լ� �����͸� �ڵ鷯�� ����ش�. 
EnemyManager::EnemyManager()
{
	setStageOneTrigger(false);
	setDiedEnemyNum(0);
	setSoundPlayNum(0);
	m_pEnemyVector.reserve(STAGE_ONE_ENEMY_NUM);
	m_pMakeHandler[ENEMY_TYPE::CHOCO] = &EnemyManager::MakeChoco;
	m_pMakeHandler[ENEMY_TYPE::ATROCE] = &EnemyManager::MakeAtroce;
	m_pMakeHandler[ENEMY_TYPE::ANCIENT_TREE] = &EnemyManager::MakeAncientTree;
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
	return;
}


// Manager�� ���� EnemyVector ��ȯ.
Vector<Enemy*>& EnemyManager::getEnemyVector()
{
	return m_pEnemyVector;
}

Vector<Enemy*>& EnemyManager::getDeleteEenemyVector()
{
	return m_DeleteEnemyVector;
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

// EnemyŸ�԰� ù ������, �׸��� �ڰ� �ִ��� ���θ� �޾� Enemy�� �������ִ� �Լ�.
void EnemyManager::MakeEnemy(const ENEMY_TYPE enemyType, const Vec2 initPosition, const bool IsSleeping)
{
	// �Լ������� m_pMakeHandler���.
	Enemy* newEnemy = (this->*m_pMakeHandler[enemyType])(initPosition);

	// Enemy ���� ó�� �κ�.
	newEnemy->setEnemyType(enemyType);
	newEnemy->setMapPointer(getMapPointer());
	m_pEnemyVector.pushBack(newEnemy);
	getMapPointer()->addChild(newEnemy);

	// Sleeping�� true��� �߰� �۾� (invisible, setIsSleeping)
	if (IsSleeping)
	{
		newEnemy->setVisible(false);
		newEnemy->setIsSleeping(true);
	}

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

// AncientTree�� ����� �Լ�.
Enemy* EnemyManager::MakeAncientTree(const Vec2 initPosition)
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(ANCIENT_TREE_PLIST);
	Enemy* newEnemy = Enemy_AncientTree::create(initPosition);

	// Boss���Դ� CollideManager�� �Ѱ��־�� �Ѵ�. (Tentacle ����)
	if (!getInnerCollideManager())
	{
		return nullptr;
	}

	if (!newEnemy)
	{
		return nullptr;
	}
	
	newEnemy->setInnerCollideManager(getInnerCollideManager());

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

void EnemyManager::StageOneSetting()
{
	// �ʱ� choco �� ���� ����.
	auto objectGroup = m_pMap->objectGroupNamed("firstChoco");
	auto objects = objectGroup->getObjects();

	for (int i = 0; i < objects.size(); i++)
	{
		auto object = objects.at(i);
		auto position = Vec2(object.asValueMap()["x"].asFloat(), object.asValueMap()["y"].asFloat());

		MakeEnemy(ENEMY_TYPE::CHOCO, position);
		m_pEnemyVector.at(i)->setIsEnemyPreemptive(false);
	}

	// Trigger�� ������ ���� �̸� ����.
	auto atroceGroup = m_pMap->getObjectGroup("Atroce");

	auto atroces = atroceGroup->getObjects();

	for (int i = 0; i < atroces.size(); ++i)
	{
		auto object = atroces.at(i);
		auto position = Vec2(object.asValueMap()["x"].asFloat(), object.asValueMap()["y"].asFloat());

		MakeEnemy(ENEMY_TYPE::ATROCE, position, true);

	}
	auto ChocoGroup = m_pMap->getObjectGroup("Choco");

	auto Chocos = ChocoGroup->getObjects();

	for (int i = 0; i < Chocos.size(); ++i)
	{
		auto object = Chocos.at(i);
		auto position = Vec2(object.asValueMap()["x"].asFloat(), object.asValueMap()["y"].asFloat());

		MakeEnemy(ENEMY_TYPE::CHOCO, position, true);

	}

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
	if (getStageOneTrigger() && m_pEnemyVector.empty())
	{
		SummonAncientTree();
	}

	return;
}

// �ʱ⿡ �����ߴ� Choco �� ������ �׾����� Ȯ���ϰ� Trigger�� �ø��� �Լ�.
bool EnemyManager::IsStageOneChocoDied()
{
	if (getDiedEnemyNum() == 2)
	{
		setStageOneTrigger(true);
		return true;
	}

	return false;
}


// StageOne�� Ʈ���Ű� �ߵ��Ǹ� ������ Enemy���� Ȱ��ȭ���ִ� �Լ�.
void EnemyManager::StageOneCreateAdditionalEnemies()
{
	auto vecSize = m_pEnemyVector.size();
	for (int i = 0; i < vecSize; ++i)
	{
		m_pEnemyVector.at(i)->setVisible(true);
		m_pEnemyVector.at(i)->setIsSleeping(false);
	}

	// Sound ���
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(TRIGGER_SOUND, false);

	return;
}

// ��� Enemy���� �׾��� ��� ������ ��ȯ���ִ� �Լ�.
void EnemyManager::SummonAncientTree()
{
	MakeEnemy(ENEMY_TYPE::ANCIENT_TREE, Vec2(900.f, 900.f));
}

// �� Update���� Enemy�� �׾����� Ȯ���� �ϰ� DeadState�� �����ϵ��� ������ش�.
// �׸��� deleteVector�� �ִ� Enemy��ü�� release���ش�.
void EnemyManager::DieCheck()
{
	for (int i = 0; i < m_pEnemyVector.size(); ++i)
	{
		auto tmpEnemy = m_pEnemyVector.at(i);
		if (tmpEnemy->getHP() <= 0)
		{
			auto diedEnemyNum = getDiedEnemyNum();
			setDiedEnemyNum(++diedEnemyNum);
			tmpEnemy->changeState<EnemyState_Dead>();
		}
	}

	for (int i = 0; i < m_DeleteEnemyVector.size(); ++i)
	{
		getMapPointer()->removeChild(m_DeleteEnemyVector.at(i));
	}

	m_DeleteEnemyVector.clear();

	return;
}