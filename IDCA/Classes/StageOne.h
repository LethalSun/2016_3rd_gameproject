#pragma once
class InputLayer;
class ManageMap;
class ManageMove;
class PlayerCharacterManager;

class Character;
class CharacterManager;
class ManageEnemyMove;

class StageOne : public Layer
{
public:
	static Scene* createScene();
	static StageOne* create();
	virtual bool init();

	void update(float delta);

	StageOne() = default;
	~StageOne() = default;

private:


	InputLayer* m_InputLayer;
	TMXTiledMap* m_pMap;
	
	

	PlayerCharacterManager* m_pPlayerCharacterManager;
	ManageMap* m_pManageMap;
	ManageMove* m_pManageMove;

	///임시 캐릭터
	Character *m_pCharacter;
	CharacterManager *m_pCharacterManager;
	unsigned int m_keyboardInput;

	Sprite *test_sprite;

	ManageEnemyMove * m_pManageEnemyMove;
};
