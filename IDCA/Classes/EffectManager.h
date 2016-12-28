#pragma once
class EffectManager : public Node
{


public:
	void MakeEffect(int damage);
	CREATE_FUNC(EffectManager);

	bool init();

	EffectManager() = default;
	~EffectManager() = default;


	EaseElasticInOut* m_pEaseEffectMove;

};

