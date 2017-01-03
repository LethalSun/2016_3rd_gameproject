#pragma once

typedef std::function <void(const char*, Vec2, Vec2, Vec2, Vec2, bool)> pFunc;

class Skill :public Component
{
public:
	Skill();
	~Skill();

	static Skill* create(const char*, const char*, const char*, const char*);

	virtual bool init(const char*, const char*, const char*, const char*);

	int GetDamage();
	bool IsSkillUsable();
	float GetMaxCooltime();
	float GetRemainCooltime();

	//init
	void SetSkillOnOff(bool);
	void SetMaxCooltime(float);
	void SetDamage(int);

	//projectile info
	void SetStartPosition(Vec2);
	void SetDirection(Vec2);
	void SetMaxRange(Vec2);
	void SetColideRange(Vec2);

	void update(float);
	void IncreaseCooltime(float);
	void GetFunc(pFunc func);

	void MakeProjectiles(bool);

private:
	String m_SkillName;

	bool m_IsUsable;
	float m_Cooltime;
	float m_MaxCooltime;
	int m_Damage;

	String m_UiImagePathUsable;
	String m_UiImagePathCoolDown;
	String m_projectileImagePath;

	Vec2 m_startPosition;
	Vec2 m_DirectionVec;
	Vec2 m_MaxRange;
	Vec2 m_ColideRange;

	//투사체를 만들어주는 함수
	pFunc MakeProjectile;
};
