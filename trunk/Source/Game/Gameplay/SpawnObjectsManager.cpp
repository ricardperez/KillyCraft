//
//  SpawnObjectsManager.cpp
//  KillyCraft
//
//  Created by Ricard Perez del Campo on 06/11/14.
//  Copyright (c) 2014 MelonGames. All rights reserved.
//

#include "SpawnObjectsManager.h"
#include "SpawnManagers.h"

namespace MelonGames
{
    namespace KillyCraft
    {
        SpawnObjectsManager::SpawnObjectsManager()
        {
            spawnSquadsManager = new SpawnSquadsManager(2.0f, 3.5f);
            spawnPowerUpsManager = new SpawnPowerUpsManager(8.0f, 10.0f);
            
            allManagers = {
                spawnSquadsManager,
                spawnPowerUpsManager
            };
        }
        
        void SpawnObjectsManager::loadEnemySquadsFromFile(const std::string& filename)
        {
            spawnSquadsManager->loadFromFile(filename);
        }
        
        void SpawnObjectsManager::setPowerUpsList(const std::vector<std::string>& names)
        {
            spawnPowerUpsManager->setList(names);
        }
        
        void SpawnObjectsManager::setMap(Map *map)
        {
            for (auto manager : allManagers)
            {
                manager->setMap(map);
            }
        }
        
        void SpawnObjectsManager::update(float dt)
        {
            for (auto manager : allManagers)
            {
                manager->update(dt);
            }
        }
        
        void SpawnObjectsManager::setSpawnHandlerForType(SpawnHandler handler, SpawnObjectsType type)
        {
            switch (type)
            {
                case SpawnObjectsType::ePowerUps:
                    spawnPowerUpsManager->setSpawnHandler(handler);
                    break;
                case SpawnObjectsType::eSquads:
                    spawnSquadsManager->setSpawnHandler(handler);
                    break;
                default:
                    break;
            }
        }
    }
}