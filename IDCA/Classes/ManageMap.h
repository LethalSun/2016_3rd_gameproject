#pragma once
class ManageMap : public Layer
{


public:
	CREATE_FUNC(ManageMap);

	TMXTiledMap* loadMap(const char* MAP_NAME);
	TMXTiledMap* m_pMap = nullptr;

	bool init();

	bool checkMap(const Vec2 background, const Vec2 position, const Vec2 unitVec, TMXTiledMap * map);



	Vec2 tileCoordForPosition(Vec2 position, TMXTiledMap * map);

	bool checkWall(Vec2 position, TMXTiledMap * map);

	bool checkChangeMap(Vec2 position, TMXTiledMap * map);



	
};

