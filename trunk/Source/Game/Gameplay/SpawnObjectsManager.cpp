//
//  SpawnObjectsManager.cpp
//  KillyCraft
//
//  Created by Ricard Perez del Campo on 06/11/14.
//  Copyright (c) 2014 MelonGames. All rights reserved.
//

#include "SpawnObjectsManager.h"
#include "GameConfig.h"
#include "MelonGames/Random.h"
#include "ObjectsFastFactory.h"
#include "Map.h"
#include "MapObject.h"
#include "MapObjectsFactory.h"
#include "Component/PositionComponent.h"

#include "base/ccMacros.h"
#include "platform/CCFileUtils.h"
#include "json/json.h"

namespace MelonGames
{
    namespace KillyCraft
    {
        SpawnObjectsManager::SpawnObjectsManager()
        : timeout(0.0f)
        , map(nullptr)
        {
        }
        
        void SpawnObjectsManager::loadEnemySquadsFromFile(const std::string& filename)
        {
            std::string fileContents = cocos2d::FileUtils::getInstance()->getStringFromFile(filename);
            
            Json::Reader reader;
            Json::Value json;
            reader.parse(fileContents, json);
            
            const auto& squadsJson = json["obj"];
            for (const auto& squadJson : squadsJson)
            {
                std::string name = squadJson["name"].asString();
                SquadTemplate squadTemplate;
                squadTemplate.name = name;
                squadTemplate.json = squadJson;
                squadTemplates.push_back(squadTemplate);
            }
        }
        
        void SpawnObjectsManager::setMap(Map *map)
        {
            this->map = map;
        }
        
        void SpawnObjectsManager::update(float dt)
        {
            assert(map && "Map must be set before update is called");
            timeout -= dt;
            
            if (timeout <= 0)
            {
                timeout = 7.0f + Random::getInstance().next() * 5.0f;
                spawnNextEnemySquad();
            }
        }
        
        void SpawnObjectsManager::spawnNextEnemySquad()
        {
            const cocos2d::Size& screenSize = map->getDefinition().screenSize;
            cocos2d::Vec2 offset(screenSize.width * 0.5f, screenSize.height);
            
            int nSquads = squadTemplates.size();
            assert(nSquads > 0);
            
            int squadIndex = std::floorf((nSquads-1) * Random::getInstance().next() + 0.5f);
            
#ifdef FORCED_SQUAD
            squadIndex = 0;
            for (const auto& squadTemplate : squadTemplates)
            {
                if (squadTemplate.name == FORCED_SQUAD)
                {
                    break;
                }
                ++squadIndex;
            }
#endif
            
            const SquadTemplate& squadTemplate = *(squadTemplates.begin() + squadIndex);
            
            std::vector<MapObject*> enemies;
            createSquad(squadTemplate, offset, enemies);
            
            for (auto enemy : enemies)
            {
                map->addObject(enemy);
            }
        }
        
        void SpawnObjectsManager::createSquad(const SquadTemplate& squadTemplate, const cocos2d::Vec2& offset, std::vector<MapObject*>& enemies)
        {
            for (const auto& enemyJson : squadTemplate.json["enemies"])
            {
                std::string enemyTemplateName = enemyJson[0].asString();
                cocos2d::Vec2 enemyOffset(enemyJson[1][0].asFloat(),
                                          enemyJson[1][1].asFloat());
                auto enemy = map->getFactory()->createObject(enemyTemplateName);
                CCASSERT(enemy, ("Could not create an enemy of type " + enemyTemplateName).c_str());
                
                if (enemy)
                {
                    auto posComponent = enemy->getOrCreate<PositionComponent>();
                    cocos2d::Vec3 position = posComponent->getPosition();
                    position.x += offset.x + enemyOffset.x;
                    position.y += offset.y + enemyOffset.y;
                    posComponent->setPosition(position);
                    
                    enemies.push_back(enemy);
                }
            }
            
            for (const auto& squadJson : squadTemplate.json["squads"])
            {
                std::string squadName = squadJson[0].asString();
                cocos2d::Vec2 squadOffset(squadJson[1][0].asFloat(),
                                          squadJson[1][1].asFloat());
                if (const SquadTemplate* squadTemplate = getSquadTemplateWithName(squadName))
                {
                    createSquad(*squadTemplate, offset + squadOffset, enemies);
                }
            }
        }
        
        const SpawnObjectsManager::SquadTemplate* SpawnObjectsManager::getSquadTemplateWithName(const std::string& name) const
        {
            for (const auto& squadTemplate : squadTemplates)
            {
                if (squadTemplate.name == name)
                {
                    return &squadTemplate;
                }
            }
            
            return nullptr;
        }
    }
}