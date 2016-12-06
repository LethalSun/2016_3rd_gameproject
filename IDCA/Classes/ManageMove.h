#pragma once

class ManageMap;

class ManageMove : public Layer
{
public:

	CREATE_FUNC(ManageMove);

	bool init();

	Vec2 update(Vec2 position, const Vec2 background, const Vec2 unitVec, TMXTiledMap * map);

	Vec2 setCharacterPosition(Vec2 position, Vec2 unitVec, const TMXTiledMap * map);

	Vec2 checkBackgroundMovable(const Vec2 position, Vec2 unitVec, const TMXTiledMap * map);



	ManageMove() = default;
	~ManageMove() = default;

private:
	ManageMap* m_manageMap;

};

