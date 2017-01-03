#pragma once

/************************************************************************/
/*
CLASS		: Skill
Author		: 김현우
역할			: 스킬의 클래스 스킬에따라서 스킬관련 데이터들을 설정해주고 투사체를 만드는 함수를
등록해 준다.
*/
/************************************************************************/
typedef std::function <void(const char*, Vec2, Vec2, Vec2, Vec2, bool)> pFunc;

class Skill :public Component
{
public:
	Skill();
	~Skill();

	static Skill* create(const char*, const char*, const char*, const char*);

	virtual bool init(const char*, const char*, const char*, const char*);

	//데미지를 받아온다
	int GetDamage();
	//스킬이 사용가능한지 알아보는 함수
	bool IsSkillUsable();
	//쿨타임 관련 함수
	float GetMaxCooltime();
	float GetRemainCooltime();

	//init
	void SetSkillOnOff(bool);
	void SetMaxCooltime(float);
	void SetDamage(int);

	//projectile info
	void SetStartPosition(Vec2);
	void SetDirection(Vec2);
	void SetMaxRange(Vec2);
	void SetColideRange(Vec2);

	void update(float);

	//쿨타임을 증가 시키는 함수
	void IncreaseCooltime(float);

	//투사체 등록 함수를 받아오는 부분
	void GetFunc(pFunc func);

	//등록받은 함수를 사용한다
	void MakeProjectiles(bool);

private:
	//스킬 이름
	String m_SkillName;

	bool m_IsUsable;
	float m_Cooltime;
	float m_MaxCooltime;
	int m_Damage;

	//이미지들의 경로
	String m_UiImagePathUsable;
	String m_UiImagePathCoolDown;
	String m_projectileImagePath;

	//시작 위치
	Vec2 m_startPosition;
	//방향
	Vec2 m_DirectionVec;
	//최대로 날아가는 거리
	Vec2 m_MaxRange;
	//충돌범위
	Vec2 m_ColideRange;

	//투사체를 만들어주는 함수
	pFunc MakeProjectile;
};
