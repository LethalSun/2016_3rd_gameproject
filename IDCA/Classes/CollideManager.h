#pragma once

class Projectile;
class Enemy;
class PlayerCharacter;
class CollideManager :public Node
{
public:
	CollideManager();
	~CollideManager();
	static CollideManager* create();
	virtual bool init();

	//ĳ������ ��ġ��, ��Ŀ�����͸� �޾ƿ��� �Լ�.
	//void SetCMCharacterPosition(const Vec2 position);
	//void SetCMCharacterAnchorPoint(const Vec2 position);
	void SetPlayerCharacterPointer(PlayerCharacter* playerCharacter);

	//���� ��ġ�� ��Ŀ�����͸� �޾ƿ��� ���ؼ� ���� �����͸� �޾ƿ��� �Լ�
	void SetCMEnemyPointer(Vector<Enemy*>& enemyVector);

	// ������ Tentacle�� ��ġ�� �޾ƿ� �÷��̾ �¾Ҵ����� ó�����ִ� �Լ�. (�ۼ��� �̱ٿ�)
	void CheckTentacleAttack(const Vec2, const float, const int, const TMXTiledMap*);

	void update(float dt);
private:
	//Vector<Projectile*> m_pvProjectile;
	Vec2 m_BackgroundPosition;
	Vector<Enemy*>* m_pvEnemy;
	PlayerCharacter * m_pPlayerCharacter;

	void CheckCollide();
	float AbsFloat(float, float);
	void CheckCharacterAttack();
	void CheckMonsterAttack();
};
