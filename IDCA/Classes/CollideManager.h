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

	//캐릭터의 위치를 맵의 위치로 바꾸기 위한 맵좌표를 얻어오는 함수
	void SetBackGroundPosition(Vec2 backgroundPosition);

	//적의 위치와 앵커포인터를 받아오기 위해서 적의 포인터를 받아오는 함수
	void SetCMEnemyPointer(Vector<Enemy*>* enemyVector);

	void update(float dt);
private:
	//공격의 앵커포인트를 계산하는 함수
	Vec2 AttackAnchorPoint();
	//Vector<Projectile*> m_pvProjectile;
	Vec2 m_BackgroundPosition;
	Vector<Enemy*>* m_pvEnemy;
	PlayerCharacter * m_pPlayerCharacter;
};
