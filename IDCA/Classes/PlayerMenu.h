#pragma once
class PlayerCharacter;

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


	PlayerCharacter*	m_pPlayer;
	Sprite*				m_pFace;
	Label*				m_pLabel;
};

