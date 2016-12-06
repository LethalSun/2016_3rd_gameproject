#pragma once

class Projectile;
class Enemy;
class CollideManager :public Node
{
public:
	CollideManager();
	~CollideManager();

	//ĳ������ ��ġ��, ��Ŀ�����͸� �޾ƿ��� �Լ�.
	void SetCMCharacterPosition(const Vec2 position);
	void SetCMCharacterAnchorPoint(const Vec2 position);

	//���� ��ġ�� ��Ŀ�����͸� �޾ƿ��� ���ؼ� ���� �����͸� �޾ƿ��� �Լ�

	void SetCMEnemyPointer(Vector<Enemy*>* enemyVector);

private:
	Vector<Projectile*> m_pvProjectile;
};
