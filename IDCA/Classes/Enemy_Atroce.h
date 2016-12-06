#pragma once

#include "Enemy.h"

class Enemy_Atroce : public Enemy
{
public :

	bool init(const Vec2) override;

	/* Create Function Re-define */
	static Enemy_Atroce* create(const Vec2 initPosition) {
		auto p = new Enemy_Atroce();
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