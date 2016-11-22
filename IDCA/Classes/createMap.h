#pragma once


class createMap : public Sprite
{
public:
	CREATE_FUNC(createMap);
	createMap();
	~createMap();

	CCTMXTiledMap* newMap;
	CCTMXLayer* background_layer1;
	CCTMXLayer* background_layer2;
	CCTMXLayer* background_layer3;
	CCTMXLayer* background_layer4;
	CCTMXLayer* background_layer5;


	CCTMXTiledMap * create(const char * mapName_1);
};

