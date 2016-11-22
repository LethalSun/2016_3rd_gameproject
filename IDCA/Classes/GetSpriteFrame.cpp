#include "pch.h"
#include "GetSpriteFrame.h"
#include "TemporaryDefine.h"

GetSpriteFrame::GetSpriteFrame()
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(TEMP_DEFINE::PLIST_FILE_NAME);
}

GetSpriteFrame::~GetSpriteFrame()
{
}