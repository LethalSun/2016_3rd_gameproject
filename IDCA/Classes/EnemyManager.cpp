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

// EnemyManager 생성자.
// EnemyVector에 Stage 1에 나올 Enemy의 개수만큼 예약해 놓고, 생성 함수 포인터를 핸들러에 담아준다. 
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


// Manager내 내부 EnemyVector 반환.
Vector<Enemy*>& EnemyManager::getEnemyVector()
{
	return m_pEnemyVector;
}

Vector<Enemy*>& EnemyManager::getDeleteEenemyVector()
{
	return m_DeleteEnemyVector;
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

// Enemy타입과 첫 포지션, 그리고 자고 있는지 여부를 받아 Enemy를 생성해주는 함수.
void EnemyManager::MakeEnemy(const ENEMY_TYPE enemyType, const Vec2 initPosition, const bool IsSleeping)
{
	// 함수포인터 m_pMakeHandler사용.
	Enemy* newEnemy = (this->*m_pMakeHandler[enemyType])(initPosition);

	// Enemy 공동 처리 부분.
	newEnemy->setEnemyType(enemyType);
	newEnemy->setMapPointer(getMapPointer());
	m_pEnemyVector.pushBack(newEnemy);
	getMapPointer()->addChild(newEnemy);

	// Sleeping이 true라면 추가 작업 (invisible, setIsSleeping)
	if (IsSleeping)
	{
		newEnemy->setVisible(false);
		newEnemy->setIsSleeping(true);
	}

	return;
}

// Choco를 만드는 함수.
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

// Atroce를 만드는 함수.
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

// AncientTree를 만드는 함수.
Enemy* EnemyManager::MakeAncientTree(const Vec2 initPosition)
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(ANCIENT_TREE_PLIST);
	Enemy* newEnemy = Enemy_AncientTree::create(initPosition);

	// Boss에게는 CollideManager를 넘겨주어야 한다. (Tentacle 관리)
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


// Vector안의 모든 Enemy에게 Player Position을 넘겨주는 함수.
void EnemyManager::ProvidePlayerPosition(const Vec2 inputPlayerPosition)
{
	auto iter = m_pEnemyVector.begin();
	for (; iter != m_pEnemyVector.end(); ++iter)
	{
		(*iter)->setPlayerPosition(inputPlayerPosition);
	}

	return;
}

// Vector번호를 넣으면 해당하는 Enemy의 포인터를 반환해 주는 함수.
Enemy* EnemyManager::FindEnemyWithIdx(const int findIdx)
{
	return m_pEnemyVector.at(findIdx);
}

// Enemy Type을 넣으면 해당하는 Enemy들을 묶어 Vector의 형태로 반환해 주는 함수.
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

// Enemy의 포인터를 넣어주면 Vector의 인덱스를 반환해주는 함수. 
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
	// 초기 choco 두 마리 생성.
	auto objectGroup = m_pMap->objectGroupNamed("firstChoco");
	auto objects = objectGroup->getObjects();

	for (int i = 0; i < objects.size(); i++)
	{
		auto object = objects.at(i);
		auto position = Vec2(object.asValueMap()["x"].asFloat(), object.asValueMap()["y"].asFloat());

		MakeEnemy(ENEMY_TYPE::CHOCO, position);
		m_pEnemyVector.at(i)->setIsEnemyPreemptive(false);
	}

	// Trigger후 생성될 몬스터 미리 생성.
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

// StageOne의 Trigger가 만족되었는지 체크해주는 함수.
// StageOne의 Update에서 호출.
void EnemyManager::StageOneTriggerCheck()
{
	// Trigger가 false일때만 확인. (중복 호출 불가)
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

// 초기에 생성했던 Choco 두 마리가 죽었는지 확인하고 Trigger를 올리는 함수.
bool EnemyManager::IsStageOneChocoDied()
{
	if (getDiedEnemyNum() == 2)
	{
		setStageOneTrigger(true);
		return true;
	}

	return false;
}


// StageOne의 트리거가 발동되면 나머지 Enemy들을 활성화해주는 함수.
void EnemyManager::StageOneCreateAdditionalEnemies()
{
	auto vecSize = m_pEnemyVector.size();
	for (int i = 0; i < vecSize; ++i)
	{
		m_pEnemyVector.at(i)->setVisible(true);
		m_pEnemyVector.at(i)->setIsSleeping(false);
	}

	// Sound 출력
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(TRIGGER_SOUND, false);

	return;
}

// 모든 Enemy들이 죽었을 경우 보스를 소환해주는 함수.
void EnemyManager::SummonAncientTree()
{
	MakeEnemy(ENEMY_TYPE::ANCIENT_TREE, Vec2(900.f, 900.f));
}

// 매 Update마다 Enemy가 죽었는지 확인을 하고 DeadState로 진입하도록 만들어준다.
// 그리고 deleteVector에 있는 Enemy객체를 release해준다.
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