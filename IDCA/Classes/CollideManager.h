#pragma once

class Projectile;
class Enemy;
class CollideManager :public Node
{
public:
	CollideManager();
	~CollideManager();

	//캐릭터의 위치와, 앵커포인터를 받아오는 함수.
	void SetCMCharacterPosition(const Vec2 position);
	void SetCMCharacterAnchorPoint(const Vec2 position);

	//적의 위치와 앵커포인터를 받아오기 위해서 적의 포인터를 받아오는 함수

	void SetCMEnemyPointer(Vector<Enemy*>* enemyVector);

private:
	Vector<Projectile*> m_pvProjectile;
};
