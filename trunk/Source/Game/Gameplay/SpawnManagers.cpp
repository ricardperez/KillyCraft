//
//  SpawnManagers.cpp
//  KillyCraft
//
//  Created by Ricard Perez del Campo on 29/01/15.
//  Copyright (c) 2015 MelonGames. All rights reserved.
//

#include "SpawnManagers.h"
#include "GameConfig.h"
#include "MelonGames/Random.h"
#include "Map.h"
#include "MapObject.h"
#include "MapObjectsFactory.h"
#include "Component/PositionComponent.h"
#include "Component/MovementStateComponents.h"
#include "Component/ViewComponent.h"
#include "View/MapView.h"
#include "View/StarsView.h"

#include "2d/CCSprite.h"
#include "base/ccMacros.h"
#include "platform/CCFileUtils.h"

namespace MelonGames
{
    namespace KillyCraft
    {
#pragma mark - SpawnManager
        SpawnManager::SpawnManager(float minTime, float varTime, bool spawnNow)
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
        
        void SpawnManager::update(float dt)
        {
            CCASSERT(map != nullptr, "Map must be set before update is called");
            timeout -= dt;
            
            if (timeout <= 0)
            {
                timeout = minTime + Random::getInstance().next() * varTime;
                spawnNextItem();
                if (spawnHandler)
                {
                    spawnHandler();
                }
            }
        }
        
#pragma mark - SpawnSquadsManager
        
        void SpawnSquadsManager::loadFromFile(const std::string& filename)
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
        void SpawnSquadsManager::spawnNextItem()
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
                    posY -= (view->getSize().height * 0.5f);
                    if (posY < minY)
                    {
                        offsetToHideFirst = (view->getSize().height * 0.5f);
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
                    float speedY = map->getView()->getStarsView()->getSpeedVector().y;
                    float timeToReachTop = std::abs(((posY - offset.y) / speedY));
                    maxDelay = std::max(maxDelay, timeToReachTop);
                }
            }
            
            timeout += maxDelay;
        }
        
        void SpawnSquadsManager::createSquad(const SquadTemplate& squadTemplate, const cocos2d::Vec2& offset, std::vector<MapObject*>& enemies)
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
                    cocos2d::Vec2 position = posComponent->getPosition();
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
        
        const SpawnSquadsManager::SquadTemplate* SpawnSquadsManager::getSquadTemplateWithName(const std::string& name) const
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
        void SpawnPowerUpsManager::setList(const std::vector<std::string> &list)
        {
            powerUpNames = list;
        }
        
        void SpawnPowerUpsManager::spawnNextItem()
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
                    powerup->getOrCreate<PositionComponent>()->setPosition(cocos2d::Vec2(posX, posY));
                    map->addObject(powerup);
                }
            }
        }
    }
}