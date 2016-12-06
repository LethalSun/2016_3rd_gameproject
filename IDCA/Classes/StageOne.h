#pragma once
class InputLayer;
class ManageMap;
class ManageMove;
class PlayerCharacterManager;

class Character;
class CharacterManager;

class EnemyManager;
class Enemy_Choco;

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

	Vec2 m_background;


	InputLayer* m_InputLayer;
	TMXTiledMap* m_pMap;
	
	
	Size m_mapSize;
	Size m_winSize;
	Size m_tileSize;

	PlayerCharacterManager* m_pPlayerCharacterManager;
	ManageMap* m_pManageMap;
	ManageMove* m_pManageMove;

	///임시 캐릭터
	Character *m_pCharacter;
	CharacterManager *m_pCharacterManager;
	unsigned int m_keyboardInput;

	// Enemy Test
	EnemyManager* m_pEnemyManager;
	Enemy_Choco* m_pEnemy;
};
