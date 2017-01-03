#pragma once
class PlayerCharacter;
class Skill;

class PlayerMenu : public Node
{
public:

	static PlayerMenu * create(PlayerCharacter * player);
	bool init(PlayerCharacter * player);
	void update(float dt);


	PlayerMenu();
	~PlayerMenu();

	int MakeHPBox();

	int MakeMaxHPBox();

	void MakeSkillBox();

	void CheckCoolTime(Skill * skill);


	PlayerCharacter*	m_pPlayer;
	Sprite*				m_pFace;
	Label*				m_pLabel;
	Skill*				m_pSkill1;

	int					skill1_MaxCoolTime;
	int					skill1_RemainCoolTime;
};

