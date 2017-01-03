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

	//투사체를 만드는 함수
	void MakeProjectile(const char*, Vec2, Vec2, Vec2, Vec2, bool);

	//맵포인터를 받아오는 함수

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

	//두번 생성되는걸 방지하기위한 변수, 스테이트 변경상의 오류 같은데
	//std::bind와 function을
	//사용해서 콜백함수로 애니메이션끝에
	//스테이트를 변경해도 오류가 잡히지 않아서
	//일단은 급하게 두번호출이 되어도 한번만 생성되도록 바꿈
	// TODO :스테이트 변경을 다른방법으로 바꾸기.
	bool m_IsProjectileMakedSameAnimation;
};
