#pragma once

#include "Enemy.h"

class Enemy_Choco : public Enemy
{
public :

	bool init(ENEMY::ENEMY_TYPE, Vec2) override;

	/* Create Function Re-define */
	static Enemy_Choco* create(ENEMY::ENEMY_TYPE enemyType, Vec2 initPosition) {
		auto p = new Enemy_Choco();
		if (p->init(enemyType, initPosition)) {
			p->autorelease();
			return p;
		}
		else {
			delete p;
			return nullptr;
		}
	}
};