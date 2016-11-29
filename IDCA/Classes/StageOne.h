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


private:
	InputLayer* m_InputLayer;
	TMXTiledMap* m_pMap;
	std::vector<TMXLayer*> m_pBackground;
	
	Size m_mapSize;
	Size m_winSize;
	Size m_tileSize;
};
