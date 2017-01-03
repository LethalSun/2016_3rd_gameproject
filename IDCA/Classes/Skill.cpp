#include "pch.h"
#include "Skill.h"

Skill::Skill()
{
}

Skill::~Skill()
{
}

Skill * Skill::create(const char* skillName, const char* UiImagePathUsable, const char* UiImagePathCoolDown, const char* projectileImagePath)
{
	Skill* pSkill(nullptr);
	pSkill = new Skill();

	if (pSkill && pSkill->init(skillName, UiImagePathUsable, UiImagePathCoolDown, projectileImagePath))
	{
		pSkill->autorelease();
		return pSkill;
	}
	else
	{
		delete pSkill;
		pSkill = nullptr;
		return pSkill;
	}
}

bool Skill::init(const char* skillName, const char* UiImagePathUsable, const char* UiImagePathCoolDown, const char* projectileImagePath)
{
	if (!(Component::init()))
	{
		return false;
	}

	m_SkillName = skillName;
	m_IsUsable = true;
	m_Cooltime = 0.f;
	m_MaxCooltime = MAX_COOL_TIME;
	m_Damage = SKILL_DAMAGE;
	m_UiImagePathUsable = UiImagePathUsable;
	m_UiImagePathCoolDown = UiImagePathCoolDown;
	m_projectileImagePath = projectileImagePath;

	setName(skillName);
	return true;
}

void Skill::SetSkillOnOff(bool val)
{
	m_IsUsable = val;
}

bool Skill::IsSkillUsable()
{
	return m_IsUsable;
}

void Skill::SetMaxCooltime(float maxTime)
{
	m_MaxCooltime = maxTime;
}

float Skill::GetMaxCooltime()
{
	return m_MaxCooltime;
}

float Skill::GetRemainCooltime()
{
	return m_Cooltime;
}

void Skill::SetStartPosition(Vec2 vec)
{
	m_startPosition = vec;
}

void Skill::SetDirection(Vec2 vec)
{
	m_DirectionVec = vec;
}

void Skill::SetMaxRange(Vec2 vec)
{
	m_MaxRange = vec;
}

void Skill::SetColideRange(Vec2 vec)
{
	m_ColideRange = vec;
}

void Skill::SetDamage(int damage)
{
	m_Damage = damage;
}

int Skill::GetDamage()
{
	return m_Damage;
}

void Skill::update(float)
{
}

void Skill::IncreaseCooltime(float dt)
{
	if (m_Cooltime >= m_MaxCooltime)
	{
		m_IsUsable = true;
		m_Cooltime = 0.f;
	}
	else
	{
		if (m_IsUsable == false)
			m_Cooltime += dt;
	}
}

void Skill::GetFunc(pFunc func)
{
	MakeProjectile = std::move(func);
}

void Skill::MakeProjectiles(bool origin)
{
	if (m_IsUsable == false)
	{
		return;
	}
	auto imagePath = m_projectileImagePath.getCString();
	MakeProjectile(imagePath, m_startPosition, m_DirectionVec, m_MaxRange, m_ColideRange, origin);
	m_IsUsable = false;
}