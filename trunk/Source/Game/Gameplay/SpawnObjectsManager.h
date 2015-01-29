//
//  SpawnObjectsManager.h
//  KillyCraft
//
//  Created by Ricard Perez del Campo on 06/11/14.
//  Copyright (c) 2014 MelonGames. All rights reserved.
//

#ifndef __KillyCraft__SpawnObjectsManager__
#define __KillyCraft__SpawnObjectsManager__

#include <string>
#include <vector>
#include <functional>

namespace MelonGames
{
    namespace KillyCraft
    {
        class Map;
        class MapObject;
        class SpawnManager;
        class SpawnSquadsManager;
        class SpawnPowerUpsManager;
        enum class SpawnObjectsType;
        
        class SpawnObjectsManager
        {
        public:
            SpawnObjectsManager();
            
            void loadEnemySquadsFromFile(const std::string& filename);
            void setPowerUpsList(const std::vector<std::string>& names);
            
            void setMap(Map* map);
            
            void update(float dt);
            
            typedef std::function<void()> SpawnHandler;
            void setSpawnHandlerForType(SpawnHandler handler, SpawnObjectsType type);
            
        private:
            SpawnSquadsManager* spawnSquadsManager;
            SpawnPowerUpsManager* spawnPowerUpsManager;
            
            std::vector<SpawnManager*> allManagers;
        };
    }
}

#endif /* defined(__KillyCraft__SpawnObjectsManager__) */
