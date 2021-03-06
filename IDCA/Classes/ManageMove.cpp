#include "pch.h"
#include "ManageMove.h"
#include "ManageMap.h"
#include "Define.h"

auto backgroundPosition = Vec2(0.f, 0.f);

bool ManageMove::init()
{
	if (!Layer::init())
	{
		return false;
	}

	return true;
}

Vec2 ManageMove::update(Vec2 position, const Vec2 background, const Vec2 unitVec, TMXTiledMap* map)
{
	m_manageMap = ManageMap::create();

	auto movable = false;
	auto checkChangeMap = false;
	backgroundPosition = background;

	checkChangeMap = m_manageMap->checkChangeMap(position - (backgroundPosition), map);
	if (checkChangeMap == true)
	{
		//changeMap("NEXTMAP");
		//return position;
	}

	movable = m_manageMap->checkBlocked(position - (backgroundPosition), unitVec, map);

	if (movable == true)
	{
		position = setCharacterPosition(position, unitVec, map);
	}

	map->setPosition(backgroundPosition);

	return position;
}

Vec2 ManageMove::setCharacterPosition(Vec2 position, Vec2 unitVec, const TMXTiledMap* map)
{
	auto backgroundMovable = false;

	unitVec = checkBackgroundMovable(position, unitVec, map);

	if (backgroundMovable == true)
	{
		return position;
	}
	return position + unitVec;
}

Vec2 ManageMove::checkBackgroundMovable(const Vec2 position, Vec2 unitVec, const TMXTiledMap* map)
{
	auto backgroundXMovable = false;
	auto backgroundYMovable = false;

	auto winSize = Director::getInstance()->getWinSize();

	if (unitVec.x < 0)
	{
		if (backgroundPosition.x < 0 && position.x <= winSize.width / 2)
		{
			backgroundPosition.x += TEMP_DEFINE::MAP_MOVE_SPEED;
			backgroundXMovable = true;
		}
		else
		{
			if (backgroundPosition.x > ENDOFTILE)
			{
				backgroundPosition.x = ENDOFTILE;
			}
			unitVec.x *= TEMP_DEFINE::CHACRACTER_MOVE_SPEED;
			if (position.x - TEMP_DEFINE::CHACRACTER_MOVE_SPEED < (SIZEOFTILE/2))
			{
				unitVec.x = 0;
			}
		}
	}
	else if (unitVec.x > 0)
	{
		if (backgroundPosition.x > -(map->getMapSize().width * SIZEOFTILE - winSize.width) && position.x >= winSize.width / 2)
		{
			backgroundPosition.x -= TEMP_DEFINE::MAP_MOVE_SPEED;
			backgroundXMovable = true;
		}
		else
		{
			if (backgroundPosition.x <= -(map->getMapSize().width * SIZEOFTILE - winSize.width))
			{
				backgroundPosition.x = -(map->getMapSize().width * SIZEOFTILE - winSize.width);
			}
			unitVec.x *= TEMP_DEFINE::CHACRACTER_MOVE_SPEED;
			if (position.x + TEMP_DEFINE::CHACRACTER_MOVE_SPEED >= winSize.width)
			{
				unitVec.x = 0;
			}
		}
	}

	if (unitVec.y < 0)
	{
		if (backgroundPosition.y < 0 && position.y <= winSize.height / 2)
		{
			backgroundPosition.y += TEMP_DEFINE::MAP_MOVE_SPEED;
			backgroundYMovable = true;
		}
		else
		{
			if (backgroundPosition.y >= ENDOFTILE)
			{
				backgroundPosition.y = ENDOFTILE;
			}
			unitVec.y *= TEMP_DEFINE::CHACRACTER_MOVE_SPEED;
			if (position.y - TEMP_DEFINE::CHACRACTER_MOVE_SPEED < (SIZEOFTILE/2))
			{
				unitVec.y = 0;
			}
		}
	}
	else if (unitVec.y > 0)
	{
		if (backgroundPosition.y > -(map->getMapSize().height * SIZEOFTILE - winSize.height) && position.y >= winSize.height / 2)
		{
			backgroundPosition.y -= TEMP_DEFINE::MAP_MOVE_SPEED;
			backgroundYMovable = true;
		}
		else
		{
			if (backgroundPosition.y <= -(map->getMapSize().height * SIZEOFTILE - winSize.height))
			{
				backgroundPosition.y = -(map->getMapSize().height * SIZEOFTILE - winSize.height);
			}
			unitVec.y *= TEMP_DEFINE::CHACRACTER_MOVE_SPEED;
			if (position.y + TEMP_DEFINE::CHACRACTER_MOVE_SPEED >= winSize.height)
			{
				unitVec.y = 0;
			}
		}
	}

	if (backgroundXMovable == true)
	{
		unitVec.x = 0;
	}
	if (backgroundYMovable == true)
	{
		unitVec.y = 0;
	}

	return unitVec;
}