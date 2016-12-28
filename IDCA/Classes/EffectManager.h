#pragma once
class EffectManager : public Node
{


public:
	void makeEffect(int damage);
	CREATE_FUNC(EffectManager);

	bool init();

	EffectManager() = default;
	~EffectManager() = default;
};

