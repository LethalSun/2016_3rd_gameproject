#pragma once
class CreateMap : public Layer
{


public:
	CREATE_FUNC(CreateMap);
	TMXTiledMap* loadMap(const char* MAP_NAME);
	TMXTiledMap* m_pMap = nullptr;

	bool init();
	
};

