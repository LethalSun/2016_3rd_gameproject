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

	//ĳ������ ��ġ�� ���� ��ġ�� �ٲٱ� ���� ����ǥ�� ������ �Լ�
	void SetBackGroundPosition(Vec2 backgroundPosition);

	//���� ��ġ�� ��Ŀ�����͸� �޾ƿ��� ���ؼ� ���� �����͸� �޾ƿ��� �Լ�
	void SetCMEnemyPointer(Vector<Enemy*>* enemyVector);

	void update(float dt);
private:
	//������ ��Ŀ����Ʈ�� ����ϴ� �Լ�
	Vec2 AttackAnchorPoint();
	//Vector<Projectile*> m_pvProjectile;
	Vec2 m_BackgroundPosition;
	Vector<Enemy*>* m_pvEnemy;
	PlayerCharacter * m_pPlayerCharacter;
};
