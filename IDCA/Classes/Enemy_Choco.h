#pragma once

#include "Enemy.h"

class Enemy_Choco : public Enemy
{
public :

	bool init(Vec2) override;

	/* Create Function Re-define */
	static Enemy_Choco* create(Vec2 initPosition) {
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