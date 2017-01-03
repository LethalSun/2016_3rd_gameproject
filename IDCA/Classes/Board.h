#pragma once


class PlayerCharacter;
class InputLayer;
class EscMenu;
class PlayerMenu;


class Board : public Node
{


public:

	static Board * create(PlayerCharacter * player);

	bool init(PlayerCharacter* player);
	void update(float deltaTime);



	Sprite*		m_pBlackBack;
	InputLayer* m_pInputLayer;
	int*		m_inputArray;
	Scene*		menuScene;
	EscMenu*	m_pEscMenu;
	PlayerMenu* m_pPlayerMenu;
	PlayerCharacter* m_pPlayerCharacter;

};

