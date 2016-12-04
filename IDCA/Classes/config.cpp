#include "pch.h"
#include "config.h"
#include "IniReader.h"
using namespace CONFIG_DEFAULT;


Config* Config::_instance = nullptr;

Config* Config::getInstance()
{
	if (!_instance)
	{
		_instance = new Config();
	}

	return _instance;
}

void Config::deleteInstance()
{
	delete _instance;
	_instance = nullptr;
	return;
}

Config::Config()
{
	m_pReadHelper = nullptr;
	iniReader = new IniReader(iniFileRoute);
	SetData();
}

void Config::SetData()
{

	/* Section Static */
	setWinSizeWidth(iniReader->ReadFloat("STATIC", "WIN_SIZE_WIDTH", intError));
	setWinSizeWidth(iniReader->ReadFloat("STATIC", "WIN_SIZE_HEIGHT", intError));

	/* Section Player */
	setPlayerPlistFileName(readStringHelper("PLAYER", "PLIST_FILE_NAME", stringError));
	setPlayerWarriorFileName(readStringHelper("PLAYER", "WARRIOR_FILE_NAME", stringError));
	setPlayerSpriteFrameFileExtention(readStringHelper("PLAYER", "SPRITE_FRAME_FILE_EXTENTION", stringError));

	/* Section Map */
	setMapName1(readStringHelper("MAP", "MAP_NAME1", stringError));

	/* Section ENEMY_CHOCO */
	setChocoPlistFileName(readStringHelper("CHOCO", "PLIST_FILE_NAME", stringError));
	setChocoSpriteFileName(readStringHelper("CHOCO", "SPRITE_FILE_NAME", stringError));
	setChocoFrameFileExtention(readStringHelper("CHOCO", "SPRITE_FRAME_FILE_EXTENTION", stringError));

	setChocoSearchingRange(iniReader->ReadFloat("CHOCO", "SEARCHING_RANGE", floatError));
	setChocoChasingRange(iniReader->ReadFloat("CHOCO", "CHASING_RANGE", floatError));
	setChocoAttackRange(iniReader->ReadFloat("CHOCO", "ATTACK_RANGE", floatError));
	setChocoMoveSpeed(iniReader->ReadFloat("CHOCO", "MOVE_SPEED", floatError));

	return;
}


char* Config::readStringHelper(const char* section, const char* key, const char* defaultStr)
{
	iniReader->ReadString(section, key, defaultStr, m_pReadHelper);
	return m_pReadHelper;
}