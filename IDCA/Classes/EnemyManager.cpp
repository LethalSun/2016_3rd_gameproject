#include "pch.h"
#include "SimpleAudioEngine.h"
#include "EnemyManager.h"
#include "Enemy_Choco.h"
#include "Enemy_Atroce.h"

const int STAGE_ONE_ENEMY_NUM = 20;
const char CHOCO_PLIST[] = "Choco.plist";
const char ATROCE_PLIST[] = "Atroce.plist";
const char TRIGGER_SOUND[] = "Sound/StageOne_triggerOn.wav";

// EnemyManager 생성자.
// EnemyVector에 Stage 1에 나올 Enemy의 개수만큼 예약해 놓고, 생성 함수 포인터를 핸들러에 담아준다. 
EnemyManager::EnemyManager()
{
	setStageOneTrigger(false);
	m_pEnemyVector.reserve(STAGE_ONE_ENEMY_NUM);
	m_pMakeHandler[ENEMY_TYPE::CHOCO] = &EnemyManager::MakeChoco;
	m_pMakeHandler[ENEMY_TYPE::ATROCE] = &EnemyManager::MakeAtroce;
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
	CCLOG("Delete EnemyManager!");
	return;
}


// Manager내 내부 EnemyVector 반환.
Vector<Enemy*>& EnemyManager::getEnemyVector()
{
	return m_pEnemyVector;
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

// TODO :: Function Stage 1 Setting 만들기. ( Choco 1,2가 죽으면 다른 몹 소환 )
void EnemyManager::StageOneSetting()
{
	// 초기 Choco Enemy 생성.
	// TODO :: Choco Enemy 매직넘버 없애기.
	MakeEnemy(ENEMY_TYPE::CHOCO, Vec2(700.f, 650.f));
	MakeEnemy(ENEMY_TYPE::CHOCO, Vec2(800.f, 650.f));

	// 초기 Choco 두 마리는 비 선공 몹으로.
	m_pEnemyVector.at(0)->setIsEnemyPreemptive(false);
	m_pEnemyVector.at(1)->setIsEnemyPreemptive(false);

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

	return;
}

// 초기에 생성했던 Choco 두 마리가 죽었는지 확인하고 Trigger를 올리는 함수.
bool EnemyManager::IsStageOneChocoDied()
{
	if (m_pEnemyVector.empty())
	{
		setStageOneTrigger(true);
		return true;
	}

	return false;
}


// StageOne의 트리거가 발동되면 나머지 Enemy들을 생성해주는 함수.
void EnemyManager::StageOneCreateAdditionalEnemies()
{
	// TODO :: 생성 위치 매직 넘버 없애기.
	MakeEnemy(ENEMY_TYPE::ATROCE, Vec2(700.f, 650.f));
	MakeEnemy(ENEMY_TYPE::ATROCE, Vec2(750.f, 700.f));
	MakeEnemy(ENEMY_TYPE::ATROCE, Vec2(800.f, 850.f));
	MakeEnemy(ENEMY_TYPE::ATROCE, Vec2(900.f, 900.f));

	// Sound 출력
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(TRIGGER_SOUND, false);

	return;
}

// 매 Update마다 Enemy가 죽었는지 확인을 하고 release를 진행해준다.
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