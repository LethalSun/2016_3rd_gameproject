#include "pch.h"
#include "config.h"

bool Config::init()
{
	if (!Component::init())
	{
		return false;
	}

	setPlayerPlist("Warrior.plist");
	setPlayerInitialSprite("WarriorA13.psd");
	setPlayerMoveSpeed(400.f);
	return true;
}

void Config::setPlayerPlist(char* src)
{
	m_pPlayerPlist = src;
	return;
}

char* Config::getPlayerPlist()
{
	return m_pPlayerPlist;
}

void Config::setPlayerInitialSprite(char* src)
{
	m_pPlayerInitialSprite = src;
	return;
}

char* Config::getPlayerInitialSprite()
{
	return m_pPlayerInitialSprite;
}

// json ���Ϸκ��� �����͸� �о���� �Լ�.
//bool Config::ReadFromFile()
//{
//}