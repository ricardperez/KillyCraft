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
#include "Signal/Signal.h"
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
            eSquads = 0,
            ePowerUps = 1,
            eTransitionStage = 2,
            eUpdateSpeed = 3,
        };
        
        class Map;
        class MapObject;
        class MapTransitionController;
        
        class SpawnObjectsManager
        {
        public:
            SpawnObjectsManager();
            
            void setMap(Map* map);
            
            void loadSquadsListFromFile(const std::string& filename);
            void setPowerUpNames(const std::vector<std::string>& names);
            void loadSpawnEventsFromFile(const std::string& filename);
            
            virtual void update(float dt);
            
            Gallant::Signal2<SpawnObjectsManager*, SpawnObjectsType>& getSpawnSignal();
            
            bool isFinished() const;
            
        private:
            struct SpawnData
            {
                float time;
                SpawnObjectsType type;
                std::string templateName;
                
                SpawnData() : time(0.0f), type(SpawnObjectsType::eSquads) {}
            };
            
            void spawnItem(const SpawnData& data);
            void spawnSquad(const std::string& templateName) const;
            void spawnPowerup(const std::string& templateName) const;
            void transitionStage();
            
            struct SquadTemplate
            {
                std::string name;
                Json::Value json;
            };
            const SquadTemplate* getSquadTemplateWithName(const std::string& name) const;
            void createSquad(const SquadTemplate& squadTemplate, const cocos2d::Vec2& offset, std::vector<MapObject*>& enemies) const;
            
            void onTransitionControllerFinished(MapTransitionController* transitionController);
            
        private:
            Map* map;
            std::vector<SpawnData> spawnItems;
            size_t currentIndex;
            
            std::vector<SquadTemplate> squadTemplates;
            std::vector<std::string> powerUpNames;
            
            Gallant::Signal2<SpawnObjectsManager*, SpawnObjectsType> spawnSignal;
            
            bool waitingForTransition;
            bool transitionStarted;
        };
    }
}

#endif /* defined(__KillyCraft__SpawnObjectsManager__) */
