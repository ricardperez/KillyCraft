//
//  ServicesManager.cpp
//  KillyCraft
//
//  Created by Ricard Pérez del Campo on 25/10/14.
//  Copyright (c) 2014 MelonGames. All rights reserved.
//

#include "ServicesManager.h"

namespace MelonGames
{
	ServicesManager& ServicesManager::getInstance()
	{
		static ServicesManager instance;
		return instance;
	}
	
	void ServicesManager::add(Service* service)
	{
		services.push_back(service);
	}
	
}