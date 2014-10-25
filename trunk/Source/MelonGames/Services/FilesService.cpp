//
//  FilesService.cpp
//  KillyCraft
//
//  Created by Ricard Pérez del Campo on 25/10/14.
//  Copyright (c) 2014 MelonGames. All rights reserved.
//

#include "FilesService.h"
#include "platform/CCFileUtils.h"

namespace MelonGames
{
	void FilesService::addDirectory(const std::string& directory)
	{
		directories.push_back(directory);
		cocos2d::FileUtils::getInstance()->addSearchPath(directory);
	}
	
	std::string FilesService::getPathForFile(const std::string& fileName) const
	{
		return cocos2d::FileUtils::getInstance()->fullPathForFilename(fileName);
	}
}