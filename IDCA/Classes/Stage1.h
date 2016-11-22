#pragma once
class Character;
class CharacterManager;
class Stage1 :public Layer
{

public:
	static Scene* createScene();
	CREATE_FUNC(Stage1);
	virtual bool init();

	virtual void update(float delta) override;
	virtual void onKeyPressed(EventKeyboard::KeyCode keyCode, Event *event) override;
	virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event) override;

	Size winSize;
	Size mapSize;
	Size tileSize;

	bool isLeft = false;
	bool isRight = false;
	bool isDown = false;
	bool isUp = false;
	float backgroundX = 0.0f;
	float backgroundY = 0.0f;

	Sprite* character = nullptr;
	CCTMXTiledMap* map = nullptr;
	CCTMXLayer* background1 = nullptr;
	CCTMXLayer* background2 = nullptr;
	CCTMXLayer* background3 = nullptr;
	CCTMXLayer* background4 = nullptr;
	CCTMXLayer* background5 = nullptr;

	void menuBackCallback(cocos2d::Ref* pSender);
	void changeMap(void);
	bool IsWall(CCPoint position);
	bool checkChangeMap(CCPoint position);
	bool backgroundMove(void);
	bool characterMove(Vec2 position);

	CCPoint tileCoordForPosition(CCPoint position);
	Vec2 setCharacterPosition(Vec2 Position, Vec2 moveVec);

private:
	unsigned int m_keyboardInput;
	Character *m_pCharacter;
	Sprite *m_pMonster;
	Sprite *m_pMonster1;
	CharacterManager *m_pCharacterManager;

	Stage1();
	~Stage1();
};
