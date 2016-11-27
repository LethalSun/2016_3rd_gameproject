#pragma once
class InputLayer;
class StageOne : public Layer
{
public:
	static Scene* createScene();
	static StageOne* create();
	virtual bool init();

	StageOne();
	~StageOne();

private:
	InputLayer* m_InputLayer;
};
