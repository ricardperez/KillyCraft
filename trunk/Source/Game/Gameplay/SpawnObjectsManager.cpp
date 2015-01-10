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
#include "Map.h"
#include "MapObject.h"
#include "MapObjectsFactory.h"
#include "Component/PositionComponent.h"
#include "Component/MovementStateComponents.h"
#include "Component/ViewComponent.h"

#include "2d/CCSprite.h"
#include "base/ccMacros.h"
#include "platform/CCFileUtils.h"
#include "json/json.h"

namespace MelonGames
{
    namespace KillyCraft
    {
        SpawnObjectsManager::SpawnObjectsManager()
        : spawnSquadsManager(2.0f, 3.5f)
        , spawnPowerUpsManager(5.0f, 5.0f)
        {
            allManagers = {
                &spawnSquadsManager,
                &spawnPowerUpsManager
            };
        }
        
        void SpawnObjectsManager::loadEnemySquadsFromFile(const std::string& filename)
        {
            spawnSquadsManager.loadFromFile(filename);
        }
        
        void SpawnObjectsManager::setPowerUpsList(const std::vector<std::string>& names)
        {
            spawnPowerUpsManager.setList(names);
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
        
#pragma mark - SpawnManager
        SpawnObjectsManager::SpawnManager::SpawnManager(float minTime, float varTime, bool spawnNow)
        : minTime(minTime)
        , varTime(varTime)
        , map(nullptr)
        , timeout(0.0f)
        {
            if (!spawnNow)
            {
                timeout = minTime + Random::getInstance().next() * varTime;
            }
        }
        
        void SpawnObjectsManager::SpawnManager::update(float dt)
        {
            assert(map && "Map must be set before update is called");
            timeout -= dt;
            
            if (timeout <= 0)
            {
                timeout = minTime + Random::getInstance().next() * varTime;
                spawnNextItem();
            }
        }
        
#pragma mark - SpawnSquadsManager
        void SpawnObjectsManager::SpawnSquadsManager::loadFromFile(const std::string& filename)
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
        void SpawnObjectsManager::SpawnSquadsManager::spawnNextItem()
        {
#ifdef FORCED_SQUAD
            if (map->getObjects().size() > 2)
            {
                return;
            }
#endif
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
            
            float maxDelay = 0.0f;
            
            float minY = std::numeric_limits<float>::max();
            float offsetToHideFirst = 0.0f;
            for (auto enemy : enemies)
            {
                map->addObject(enemy);
                
                float posY = enemy->get<PositionComponent>()->getPosition().y;
                if (auto view = enemy->get<ViewComponent>())
                {
                    if (auto sprite = view->getSprite())
                    {
                        posY -= (sprite->getContentSize().height * 0.5f);
                        if (posY < minY)
                        {
                            offsetToHideFirst = (sprite->getContentSize().height * 0.5f);
                        }
                    }
                }
            }
            
            for (auto enemy : enemies)
            {
                auto posComponent = enemy->get<PositionComponent>();
                posComponent->movePositionY(offsetToHideFirst);
                float posY = posComponent->getPosition().y;
                
                if (posY > offset.y)
                {
                    if (auto moveState = enemy->get<MoveLinearStateComponent>())
                    {
                        float timeToReachTop = std::abs(((posY - offset.y) / moveState->getMovementPerSecond().y));
                        maxDelay = std::max(maxDelay, timeToReachTop);
                    }
                }
            }
            
            timeout += maxDelay;
        }
        
        void SpawnObjectsManager::SpawnSquadsManager::createSquad(const SquadTemplate& squadTemplate, const cocos2d::Vec2& offset, std::vector<MapObject*>& enemies)
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
        
        const SpawnObjectsManager::SpawnSquadsManager::SquadTemplate* SpawnObjectsManager::SpawnSquadsManager::getSquadTemplateWithName(const std::string& name) const
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
        
#pragma mark - SpawnPowerUpsManager
        void SpawnObjectsManager::SpawnPowerUpsManager::setList(const std::vector<std::string> &list)
        {
            powerUpNames = list;
        }
        
        void SpawnObjectsManager::SpawnPowerUpsManager::spawnNextItem()
        {
            CCASSERT(!powerUpNames.empty(), "At least one powerup should be loaded");
            
#ifdef FORCED_SQUAD
            return;
#endif
            
            if (!powerUpNames.empty())
            {
                int index = Random::getInstance().nextIntInRange(0, powerUpNames.size(), true, false);
                const std::string& name = *(powerUpNames.begin() + index);
                if (auto powerup = map->getFactory()->createObject(name))
                {
                    float posX = map->getDefinition().screenSize.width * 0.5f;
                    float posY = map->getDefinition().screenSize.height + 50.0f;
                    powerup->getOrCreate<PositionComponent>()->setPosition(cocos2d::Vec3(posX, posY, 0.0f));
                    map->addObject(powerup);
                }
            }
        }
    }
}