#pragma once
class EffectManager : public Node
{


public:
	void MakeEffect(int damage);
	void afterEnd();
	CREATE_FUNC(EffectManager);

	bool init();

	EffectManager() = default;
	~EffectManager() = default;

	char damageBuf[100];

	EaseElasticInOut*		m_pEaseEffectMove;
	Action*					m_pRunResult;
	Sprite*					m_pEffect;
	LabelBMFont*			m_pDamageLabel;
};

