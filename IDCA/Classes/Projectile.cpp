#include "pch.h"
#include "Projectile.h"

Projectile::Projectile()
{
}

Projectile::~Projectile()
{
}

Projectile * Projectile::create(const char *spriteImagePath, Vec2 startPosition, Vec2 direction, Vec2 maxRange, Vec2 colideRange, bool isCharacterOrignated)
{
	auto pProjectile = new(std::nothrow) Projectile();

	if (pProjectile && pProjectile->init(spriteImagePath, startPosition, direction, maxRange, colideRange, isCharacterOrignated))
	{
		pProjectile->autorelease();
		return pProjectile;
	}
	else
	{
		delete pProjectile;
		pProjectile = nullptr;
		return pProjectile;
	}
}

bool Projectile::init(const char *spriteImagePath, Vec2 startPosition, Vec2 direction, Vec2 maxRange, Vec2 colideRange, bool isCharacterOrignated)
{
	if (!(Node::init()))
	{
		return false;
	}

	m_pSprite = Sprite::create(spriteImagePath);

	m_startPosition = startPosition;
	m_DirectionVec = direction;
	m_MaxRange = maxRange;
	m_ColideRange = colideRange;

	SetSprite();

	m_damage = SKILL_DAMAGE;
	m_isCharacterOrignated = isCharacterOrignated;
	m_Disappeared = false;
	m_IsAttackChecked = false;
	return true;
}

Sprite * Projectile::GetSprite()
{
	return m_pSprite;
}

Vec2 Projectile::GetColideRange()
{
	return m_ColideRange;
}

Vec2 Projectile::GetColidePosition()
{
	if (m_pSprite == nullptr)
	{
		return Vec2(0.f, 0.f);
	}
	return m_pSprite->getPosition();
}

int Projectile::GetDamage()
{
	return m_damage;
}

bool Projectile::IsFromCharacter()
{
	return m_isCharacterOrignated;
}

bool Projectile::IsAttackChecked()
{
	return m_IsAttackChecked;
}

bool Projectile::IsDisappear()
{
	return m_Disappeared;
}

void Projectile::SetStartPosition(Vec2 start)
{
	m_startPosition = start;
}

void Projectile::SetDirection(Vec2 direction)
{
	m_DirectionVec = direction;
}

void Projectile::SetMaxRange(Vec2 max)
{
	m_MaxRange = max;
}

void Projectile::SetColideRange(Vec2 range)
{
	m_ColideRange = range;
}

void Projectile::SetDamage(int damage)
{
	m_damage = damage;
}
void Projectile::SetOrign(bool b)
{
	m_isCharacterOrignated = b;
}

void Projectile::SetIsAttackChecked(bool)
{
	m_IsAttackChecked = true;
}

void Projectile::SetDisappear(bool b)
{
	m_Disappeared = b;
}

void Projectile::SetInvisible()
{
	m_pSprite->setVisible(false);
}

void Projectile::Erase()
{
	m_Disappeared = true;
}

bool Projectile::SetSprite()
{
	m_pSprite->setPosition(m_startPosition);
	m_pSprite->setScale(SCALE_PROJECTILE);
	auto x = m_DirectionVec.x * m_MaxRange.x;
	auto y = m_DirectionVec.y * m_MaxRange.y;
	auto endPoint = Vec2(x, y);
	auto move = MoveBy::create(SKILL_DURATION, endPoint);
	auto eraseSelf = RemoveSelf::create();
	auto callFunc = CallFunc::create(CC_CALLBACK_0(Projectile::Erase, this));
	auto seq = Sequence::create(move, callFunc, eraseSelf, nullptr);
	auto rotate = RotateBy::create(SKILL_ROTATE_TIME, SKILL_ROTATE_DEGREE);
	auto rotate5 = Repeat::create(rotate, 10);
	auto spawn = Spawn::createWithTwoActions(rotate5, seq);
	m_pSprite->runAction(spawn);
	addChild(m_pSprite);
	return true;
}