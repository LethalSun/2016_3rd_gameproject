#pragma once
class InputLayer;
class CreateMap;


class StageOne : public Layer
{
public:
	static Scene* createScene();
	static StageOne* create();
	virtual bool init();

	void update(float delta);

	StageOne();
	~StageOne();

private:
	InputLayer* m_InputLayer;
	TMXTiledMap* m_pMap;
	
};