#pragma once

/************************************************************************/
/*
CLASS		: CollideManager
Author		: ������
����			: ĳ���Ϳ� �� �׸��� ����ü���� �浹�� üũ �Ѵ�.

�̰͵� ������ �����͸� ��� �ִ� ���� �ƴ϶�
�ݹ��Լ��� ���� �ϴ� ���� �� ��� �ҰͰ�����
�ϴ��� �����͸� �����ϸ鼭 �Ź� üũ�� ���ش�.
*/
/************************************************************************/

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

	//ĳ������ �����͸� �޾ƿ��� �Լ�
	void SetPlayerCharacterPointer(PlayerCharacter* playerCharacter);

	//���� ��ġ�� ��Ŀ�����͸� �޾ƿ��� ���ؼ� ���� �����͸� �޾ƿ��� �Լ�
	void SetCMEnemyPointer(Vector<Enemy*>& enemyVector);

	//����ü�� ����� �Լ�
	void MakeProjectile(const char*, Vec2, Vec2, Vec2, Vec2, bool);

	//�������͸� �޾ƿ��� �Լ�
	void SetMapPointer(TMXTiledMap*);

	// ������ Tentacle�� ��ġ�� �޾ƿ� �÷��̾ �¾Ҵ����� ó�����ִ� �Լ�. (�ۼ��� �̱ٿ�)
	void CheckTentacleAttack(const Vec2, const float, const int, const TMXTiledMap*);

	void update(float dt);

private:
	//������ �ִ� �����͵��� ����
	Vec2 m_BackgroundPosition;

	Vector<Enemy*>* m_pvEnemy;

	PlayerCharacter * m_pPlayerCharacter;

	Vector<Projectile*> m_vProjectile;

	TMXTiledMap* m_pMap;

	//�浹�� üũ�ϴ� �Լ�
	void CheckCollide();
	void CheckCharacterAttack();
	void CheckMonsterAttack();
	void CheckProjectileColide();

	//���밪�� ����ϴ� �Լ�
	float AbsFloat(float, float);

	//����ü�� �����ִ� �Լ�
	void EraseProjectile();
};
