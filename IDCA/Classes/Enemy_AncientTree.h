#pragma once

#include "Enemy.h"

class Enemy_AncientTree : public Enemy
{
public :
	
	bool init(const Vec2) override;

	/* Create Function Re-define */
	static Enemy_AncientTree* create(const Vec2 initPosition) {
		auto p = new Enemy_AncientTree();
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