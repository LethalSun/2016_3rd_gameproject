#include "pch.h"
#include "config.h"

void Config::init()
{
	setPlayerPlist("Warrior.plist");
	setPlayerInitialSprite("WalkingFront01.png");
	setPlayerMoveSpeed(400.f);
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