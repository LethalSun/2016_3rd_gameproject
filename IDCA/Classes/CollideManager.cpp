#include "pch.h"
#include "CollideManager.h"
#include "Enemy.h"
#include "Enemy_Atroce.h"
#include "Enemy_Choco.h"
#include "PlayerCharacter.h"
#include "EnemyManager.h"
#include "Projectile.h"
#include "SimpleAudioEngine.h"
#include <functional>
#include <math.h>

CollideManager::CollideManager()
{
}

CollideManager::~CollideManager()
{
}

CollideManager * CollideManager::create()
{
	auto pMaker = new(std::nothrow) CollideManager();
	if (pMaker&&pMaker->init())
	{
		pMaker->autorelease();
		return pMaker;
	}
	else
	{
		delete pMaker;
		pMaker = nullptr;
		return pMaker;
	}
}

bool CollideManager::init()
{
	if (!(Node::init()))
	{
		return false;
	}

	m_pvEnemy = nullptr;
	m_pPlayerCharacter = nullptr;
	m_BackgroundPosition = Vec2(0, 0);
	m_IsProjectileMakedSameAnimation = false;
	scheduleUpdate();

	return true;
}

void CollideManager::SetPlayerCharacterPointer(PlayerCharacter * playerCharacter)
{
	m_pPlayerCharacter = playerCharacter;
	m_pPlayerCharacter->GetFunc(std::bind(&CollideManager::MakeProjectile, this,
		std::placeholders::_1,
		std::placeholders::_2,
		std::placeholders::_3,
		std::placeholders::_4,
		std::placeholders::_5,
		std::placeholders::_6));
}

void CollideManager::SetCMEnemyPointer(Vector<Enemy*>& enemyVector)
{
	m_pvEnemy = &enemyVector;
}

void CollideManager::MakeProjectile(const char *spriteImagePath, Vec2 startPosition, Vec2 direction, Vec2 maxRange, Vec2 colideRange, bool isCharacterOrignated)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sound/Warrior_skill.wav", false);

	auto tempProjectile = Projectile::create(spriteImagePath, startPosition, direction, maxRange, colideRange, isCharacterOrignated);
	if (tempProjectile != nullptr)
	{
		m_vProjectile.pushBack(tempProjectile);
		m_pMap->addChild(tempProjectile);
	}
}

void CollideManager::SetMapPointer(TMXTiledMap * p)
{
	m_pMap = p;
}

void CollideManager::update(float dt)
{
	EraseProjectile();
	CheckCollide();
}

void CollideManager::CheckCollide()
{
	//캐릭터 공격 체크
	CheckCharacterAttack();
	CheckMonsterAttack();
	CheckProjectileColide();
}

float CollideManager::AbsFloat(float f1, float f2)
{
	float fr;
	if (f1 > f2)
	{
		fr = f1 - f2;
	}
	else
	{
		fr = f2 - f1;
	}
	return fr;
}

//캐릭터->몬스터 공격체크
void CollideManager::CheckCharacterAttack()
{
	SetCMEnemyPointer(EnemyManager::getInstance()->getEnemyVector());
	if (m_pPlayerCharacter->GetState() != STATE::ATTACK)
	{
		return;
	}

	if (m_pPlayerCharacter->IsAttackChecked() == true)
	{
		return;
	}

	// TODO :: Enemy를 지우면 여기서 자꾸 충돌이 일어나는데 어떻게 해결해야 할지?
	Vector<Enemy*>::iterator iter = m_pvEnemy->begin();
	for (; iter != m_pvEnemy->end(); ++iter)
	{
		// X collide
		auto xMin = m_pPlayerCharacter->GetAttackRange().x / 2
			+ (*iter)->getBodyRangeForCollide().x / 2;

		auto x = AbsFloat(m_pPlayerCharacter->GetAttackAnchorPoint().x,
			(*iter)->getBodyAnchorPoint().x);
		// Y collide
		auto yMin = m_pPlayerCharacter->GetAttackRange().y / 2
			+ (*iter)->getBodyRangeForCollide().y / 2;
		auto y = AbsFloat(m_pPlayerCharacter->GetAttackAnchorPoint().y,
			(*iter)->getBodyAnchorPoint().y);

		if ((xMin >= x) && (yMin >= y))
		{
			auto damage = m_pPlayerCharacter->GetDamage();
			(*iter)->setAttackedDamage(damage);
			m_pPlayerCharacter->SetAttackChecked();
		}
	}
}
//몬스터->캐릭터 공격체크
void CollideManager::CheckMonsterAttack()
{
	Vector<Enemy*>::iterator iter = m_pvEnemy->begin();
	for (; iter != m_pvEnemy->end(); ++iter)
	{
		if ((*iter)->getState()->returnStateNumber() != ENEMY_STATE_TYPE::ATTACKING)
		{
			continue;
		}
		if ((*iter)->getAttackChecked() == true)
		{
			continue;
		}

		// X collide
		auto xMin = m_pPlayerCharacter->GetBodyRange().x / 2
			+ (*iter)->getAttackRangeForCollide().x / 2;

		auto x = AbsFloat(m_pPlayerCharacter->GetBodyAnchorPoint().x,
			(*iter)->getAttackAnchorPoint().x);

		// Y collide
		auto yMin = m_pPlayerCharacter->GetBodyRange().y / 2
			+ (*iter)->getAttackRangeForCollide().y / 2;
		auto y = AbsFloat(m_pPlayerCharacter->GetBodyAnchorPoint().y,
			(*iter)->getAttackAnchorPoint().y);

		if ((xMin >= x) && (yMin >= y))
		{
			auto damage = (*iter)->getDamage();
			(*iter)->setAttackChecked(true);
			m_pPlayerCharacter->SetAttackedDamage(damage);
		}
	}
}

void CollideManager::CheckProjectileColide()
{
	for (auto itIsProjectile : m_vProjectile)
	{
		if (itIsProjectile->IsAttackChecked() == true)
		{
			continue;
		}

		for (auto itIsEnemy : *m_pvEnemy)
		{
			// X collide
			auto xMin = itIsProjectile->GetColideRange().x / 2
				+ itIsEnemy->getBodyRangeForCollide().x / 2;

			auto xp = itIsProjectile->GetColidePosition().x;
			auto xe = itIsEnemy->getBodyAnchorPoint().x;

			auto x = AbsFloat(xp, xe);

			// Y collide
			auto yMin = itIsProjectile->GetColideRange().y / 2
				+ itIsEnemy->getBodyRangeForCollide().y / 2;
			auto y = AbsFloat(itIsProjectile->GetColidePosition().y,
				itIsEnemy->getBodyAnchorPoint().y);

			if ((xMin >= x) && (yMin >= y))
			{
				auto damage = itIsProjectile->GetDamage();
				itIsEnemy->setAttackedDamage(damage);
				itIsProjectile->SetIsAttackChecked(true);
				itIsProjectile->SetInvisible();
			}
		}
	}
}

void CollideManager::EraseProjectile()
{
	Vector<Projectile*>::iterator iter = m_vProjectile.begin();
	while (iter != m_vProjectile.end())
	{
		if ((*iter)->IsDisappear() == true)
		{
			iter = m_vProjectile.erase(iter);
		}
		else
		{
			++iter;
		}
	}
}

// 텐타클 생성 범위, 공격 범위, 데미지와 맵 포인터를 인자로 받아 캐릭터와의 충돌 처리를 담당해주는 함수. (작성자 : 이근원)
void CollideManager::CheckTentacleAttack(const Vec2 tentaclePosition, const float range, const int damage, const TMXTiledMap* mapPointer)
{
	auto x = AbsFloat(m_pPlayerCharacter->getPosition().x - mapPointer->getPosition().x, tentaclePosition.x);
	auto y = AbsFloat(m_pPlayerCharacter->getPosition().y - mapPointer->getPosition().y, tentaclePosition.y);

	auto distance = sqrt(x * x + y * y);
	if (distance < range)
	{
		m_pPlayerCharacter->SetAttackedDamage(damage);
	}

	return;
}