//
//  SpawnManagers.h
//  KillyCraft
//
//  Created by Ricard Perez del Campo on 29/01/15.
//  Copyright (c) 2015 MelonGames. All rights reserved.
//

#ifndef __KillyCraft__SpawnManagers__
#define __KillyCraft__SpawnManagers__

#include <vector>
#include <string>
#include "json/json.h"

namespace cocos2d
{
    class Vec2;
}

namespace MelonGames
{
    namespace KillyCraft
    {
        enum class SpawnObjectsType
        {
            eSquads,
            ePowerUps
        };
        
        class Map;
        class MapObject;
        class SpawnManager
        {
        public:
            
            SpawnManager(float minTime, float varTime, bool spawnNow);
            
            virtual void update(float dt);
            virtual void spawnNextItem() = 0;
            
            void setMap(Map* map) { this->map = map; }
            
            typedef std::function<void()> SpawnHandler;
            void setSpawnHandler(SpawnHandler spawnHandler) { this->spawnHandler = spawnHandler; }
            
        private:
            SpawnManager();
            
        protected:
            const float minTime;
            const float varTime;
            Map* map;
            float timeout;
            SpawnHandler spawnHandler;
        };
        
        class SpawnSquadsManager : public SpawnManager
        {
        public:
            SpawnSquadsManager(float minTime, float varTime) : SpawnManager(minTime, varTime, true) {};
            struct SquadTemplate
            {
                std::string name;
                Json::Value json;
            };
            
            void loadFromFile(const std::string& filename);
            void spawnNextItem() override;
            void createSquad(const SquadTemplate& squadTemplate, const cocos2d::Vec2& offset, std::vector<MapObject*>& enemies);
            const SquadTemplate* getSquadTemplateWithName(const std::string& name) const;
            
        private:
            std::vector<SquadTemplate> squadTemplates;
        };
        
        class SpawnPowerUpsManager : public SpawnManager
        {
        public:
            SpawnPowerUpsManager(float minTime, float varTime) : SpawnManager(minTime, varTime, false) {};
            void setList(const std::vector<std::string>& list);
            void spawnNextItem() override;
            
        private:
            std::vector<std::string> powerUpNames;
            
        };
    }
}

#endif /* defined(__KillyCraft__SpawnManagers__) */
