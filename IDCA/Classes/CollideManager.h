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

	//캐릭터의 위치와, 앵커포인터를 받아오는 함수.
	//void SetCMCharacterPosition(const Vec2 position);
	//void SetCMCharacterAnchorPoint(const Vec2 position);
	void SetPlayerCharacterPointer(PlayerCharacter* playerCharacter);

	//적의 위치와 앵커포인터를 받아오기 위해서 적의 포인터를 받아오는 함수
	void SetCMEnemyPointer(Vector<Enemy*>* enemyVector);

	void update(float dt);
private:
	//Vector<Projectile*> m_pvProjectile;
	Vec2 m_BackgroundPosition;
	Vector<Enemy*>* m_pvEnemy;
	PlayerCharacter * m_pPlayerCharacter;

	void CheckCollide();
	float AbsFloat(float, float);
	void CheckCharacterAttack();
};
