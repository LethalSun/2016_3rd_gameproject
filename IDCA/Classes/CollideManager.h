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

	//����ü�� ����� �Լ�
	void MakeProjectile(const char*, Vec2, Vec2, Vec2, Vec2, bool);

	//�������͸� �޾ƿ��� �Լ�

	void SetMapPointer(TMXTiledMap*);

	void update(float dt);
private:
	//Vector<Projectile*> m_pvProjectile;
	Vec2 m_BackgroundPosition;
	Vector<Enemy*>* m_pvEnemy;
	PlayerCharacter * m_pPlayerCharacter;
	Vector<Projectile*> m_vProjectile;

	TMXTiledMap* m_pMap;

	void CheckCollide();
	float AbsFloat(float, float);
	void CheckCharacterAttack();
	void CheckMonsterAttack();
	void CheckProjectileColide();
	void EraseProjectile();

	//�ι� �����Ǵ°� �����ϱ����� ����, ������Ʈ ������� ���� ������
	//std::bind�� function��
	//����ؼ� �ݹ��Լ��� �ִϸ��̼ǳ���
	//������Ʈ�� �����ص� ������ ������ �ʾƼ�
	//�ϴ��� ���ϰ� �ι�ȣ���� �Ǿ �ѹ��� �����ǵ��� �ٲ�
	// TODO :������Ʈ ������ �ٸ�������� �ٲٱ�.
	bool m_IsProjectileMakedSameAnimation;
};
