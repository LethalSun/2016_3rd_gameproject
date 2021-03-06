#pragma once

/*
	Enemy_Choco
	작성자 : 이근원
*/

#include "Enemy.h"

class Enemy_Choco : public Enemy
{
public :

	bool init(const Vec2) override;
	bool isAttacked;


	/* Create Function Re-define */
	static Enemy_Choco* create(const Vec2 initPosition) {
		auto p = new Enemy_Choco();
		if (p->init(initPosition)) {
			p->autorelease();
			return p;
		}
		else {
			delete p;
			return nullptr;
		}
	}
};