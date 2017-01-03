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
	void SetCMEnemyPointer(Vector<Enemy*>& enemyVector);

	// 보스의 Tentacle의 위치를 받아와 플레이어가 맞았는지를 처리해주는 함수. (작성자 이근원)
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
