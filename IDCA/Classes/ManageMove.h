#pragma once

class ManageMap;

class ManageMove : public Layer
{
public:

	CREATE_FUNC(ManageMove);

	bool init();

	Vec2 update(Vec2 position, Vec2 background, Vec2 unitVec, TMXTiledMap * map);

	Vec2 setCharacterPosition(Vec2 position, Vec2 unitVec, TMXTiledMap * map);

	bool checkBackgroundMovable(Vec2 position, Vec2 unitVec, TMXTiledMap * map);



	ManageMove() = default;
	~ManageMove() = default;

private:
	ManageMap* m_manageMap;

};

