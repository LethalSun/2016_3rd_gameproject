#pragma once

/************************************************************************/
/*
CLASS		: CollideManager
Author		: 김현우
역할			: 캐릭터와 적 그리고 투사체간의 충돌을 체크 한다.

이것도 각각의 포인터를 들고 있는 것이 아니라
콜백함수로 구현 하는 것이 더 깔끔 할것같지만
일단은 포인터를 보관하면서 매번 체크를 해준다.
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

	//캐릭터의 포인터를 받아오는 함수
	void SetPlayerCharacterPointer(PlayerCharacter* playerCharacter);

	//적의 위치와 앵커포인터를 받아오기 위해서 적의 포인터를 받아오는 함수
	void SetCMEnemyPointer(Vector<Enemy*>& enemyVector);

	//투사체를 만드는 함수
	void MakeProjectile(const char*, Vec2, Vec2, Vec2, Vec2, bool);

	//맵포인터를 받아오는 함수
	void SetMapPointer(TMXTiledMap*);

	// 보스의 Tentacle의 위치를 받아와 플레이어가 맞았는지를 처리해주는 함수. (작성자 이근원)
	void CheckTentacleAttack(const Vec2, const float, const int, const TMXTiledMap*);

	void update(float dt);

private:
	//가지고 있는 포인터들의 변수
	Vec2 m_BackgroundPosition;

	Vector<Enemy*>* m_pvEnemy;

	PlayerCharacter * m_pPlayerCharacter;

	Vector<Projectile*> m_vProjectile;

	TMXTiledMap* m_pMap;

	//충돌을 체크하는 함수
	void CheckCollide();
	void CheckCharacterAttack();
	void CheckMonsterAttack();
	void CheckProjectileColide();

	//절대값을 계산하는 함수
	float AbsFloat(float, float);

	//투사체를 지워주는 함수
	void EraseProjectile();
};
