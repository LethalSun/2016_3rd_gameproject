#pragma once
class Enemy;

class ManageMap : public Layer
{


public:
	CREATE_FUNC(ManageMap);

	TMXTiledMap* loadMap(const char* MAP_NAME);
	TMXTiledMap* m_pMap = nullptr;

	bool init();



	Vec2 tileCoordForPosition(const Vec2 position, const TMXTiledMap * map);

	bool checkWall(const Vec2 position,const TMXTiledMap * map);
	bool checkWall(const Vec2 position, const TMXTiledMap * map, Vector<Enemy*>* enemyVector);
	
	bool checkChangeMap(const Vec2 position,const TMXTiledMap * map);

	Vec2 getStartPosition();
	Vec2 startPosition;

	
};

