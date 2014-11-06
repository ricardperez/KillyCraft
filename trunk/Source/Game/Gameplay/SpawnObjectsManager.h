//
//  SpawnObjectsManager.h
//  KillyCraft
//
//  Created by Ricard Perez del Campo on 06/11/14.
//  Copyright (c) 2014 MelonGames. All rights reserved.
//

#ifndef __KillyCraft__SpawnObjectsManager__
#define __KillyCraft__SpawnObjectsManager__

namespace MelonGames
{
    namespace KillyCraft
    {
        class Map;
        
        class SpawnObjectsManager
        {
        public:
            SpawnObjectsManager();
            
            void setMap(Map* map);
            
            void update(float dt);
            
        private:
            void spawnNextEnemySquad();
            
        private:
            float timeout;
            Map* map;
        };
    }
}

#endif /* defined(__KillyCraft__SpawnObjectsManager__) */
