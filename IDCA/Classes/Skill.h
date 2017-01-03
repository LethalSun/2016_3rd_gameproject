#pragma once

class Skill :public Component
{

public:
	Skill();
	~Skill();

private:
	bool m_IsUsable;
	float m_Cooltime;
	float m_MaxCooltime;
	int damage;
	const String m_UiImagePathUsable;
	const String m_UiImagePathCoolDown;
	const String m_projectileImagePath;
};

