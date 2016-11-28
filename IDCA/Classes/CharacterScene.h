#pragma once
class Character;
class CharacterManager;


class CharacterScene :public Layer
{
private:
	enum KEY_BOARD_INPUT
	{
		UP = 1,
		DOWN = 2,
		RIGHT = 4,
		LEFT = 8,
		A = 16
	};
public:
	static Scene* createScene();
	CREATE_FUNC(CharacterScene);
	virtual bool init();

	virtual void update(float delta) override;
	virtual void onKeyPressed(EventKeyboard::KeyCode keyCode, Event *event) override;
	virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event) override;

	void menuBackCallback(cocos2d::Ref* pSender);

private:
	unsigned int m_keyboardInput;
	Character *m_pCharacter;
	Sprite *m_pMonster;
	Sprite *m_pMonster1;
	CharacterManager *m_pCharacterManager;

	CharacterScene();
	~CharacterScene();
};
