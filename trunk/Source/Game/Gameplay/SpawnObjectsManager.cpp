//
//  SpawnObjectsManager.cpp
//  KillyCraft
//
//  Created by Ricard Perez del Campo on 06/11/14.
//  Copyright (c) 2014 MelonGames. All rights reserved.
//

#include "SpawnObjectsManager.h"
#include "MelonGames/Random.h"
#include "ObjectsFastFactory.h"
#include <cassert>

namespace MelonGames
{
    namespace KillyCraft
    {
        SpawnObjectsManager::SpawnObjectsManager()
        : timeout(0.0f)
        , map(nullptr)
        {
            
        }
        
        void SpawnObjectsManager::setMap(Map *map)
        {
            this->map = map;
        }
        
        void SpawnObjectsManager::update(float dt)
        {
            assert(map && "Map must be set before update is called");
            timeout -= dt;
            
            if (timeout == 0)
            {
                timeout = 7.0f + Random::getInstance().next() * 5.0f;
                spawnNextEnemySquad();
            }
        }
        
        void SpawnObjectsManager::spawnNextEnemySquad()
        {
            auto enemy = ObjectsFastFactory::createEnemyObject();
        }
    }
}