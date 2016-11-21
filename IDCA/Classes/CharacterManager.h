#pragma once
class Character;

class CharacterManager :public Node
{
	virtual bool init();

	CREATE_FUNC(CharacterManager);

	void update(float delta);
	void GetCharacterInfo(Character* character);
	void GetSpriteInfo(Sprite* sprite);
	bool CheckHit();
	bool GetHitInfo();
	void MakeRedBox(Vec2 position, Vec2 boxInfo, int tag);
	Vec2 Distance(Vec2 a, Vec2 b);
	Vec2 AttackAnchorPoint();

private:
	int m_BoxTagMonster;
	int m_BoxTagCharacter;
	bool m_HitHit;
	int m_CharacterState;
	int m_CharacterBeforstate;
	Vec2 m_CharacterPosition;
	Vec2 m_CharacterAttackDirection;
	Vec2 m_CharacterAttackRange;
	Vec2 m_CharacterBeAttackedBox;
	Vec2 m_TargetPosition;
	Vec2 m_TargetBeAttackefBox;
};
