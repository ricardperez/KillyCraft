//
//  SpawnObjectsManager.h
//  KillyCraft
//
//  Created by Ricard Perez del Campo on 06/11/14.
//  Copyright (c) 2014 MelonGames. All rights reserved.
//

#ifndef __KillyCraft__SpawnObjectsManager__
#define __KillyCraft__SpawnObjectsManager__

#include "json/value.h"
#include <string>
#include <vector>

namespace cocos2d
{
    class Vec2;
}

namespace MelonGames
{
    namespace KillyCraft
    {
        class Map;
        class MapObject;
        
        class SpawnObjectsManager
        {
        public:
            SpawnObjectsManager();
            
            void loadEnemySquadsFromFile(const std::string& filename);
            
            void setMap(Map* map);
            
            void update(float dt);
            
        private:
            struct SquadTemplate
            {
                std::string name;
                Json::Value json;
            };
            
        private:
            void spawnNextEnemySquad();
            void createSquad(const SquadTemplate& squadTemplate, const cocos2d::Vec2& offset, std::vector<MapObject*>& enemies);
            const SquadTemplate* getSquadTemplateWithName(const std::string& name) const;
            
        private:
            float timeout;
            Map* map;
            
            std::vector<SquadTemplate> squadTemplates;
        };
    }
}

#endif /* defined(__KillyCraft__SpawnObjectsManager__) */
