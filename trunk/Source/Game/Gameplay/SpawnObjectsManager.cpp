//
//  SpawnObjectsManager.cpp
//  KillyCraft
//
//  Created by Ricard Perez del Campo on 06/11/14.
//  Copyright (c) 2014 MelonGames. All rights reserved.
//

#include "SpawnObjectsManager.h"
#include "Map.h"
#include "MapTime.h"
#include "MapObject.h"
#include "MapObjectsFactory.h"
#include "MapObjectInspector.h"
#include "MapTransitionController.h"
#include "View/MapView.h"
#include "View/StarsView.h"
#include "Component/PositionComponent.h"
#include "Component/ViewComponent.h"

#include "base/ccMacros.h"
#include "platform/CCFileUtils.h"

namespace MelonGames
{
    namespace KillyCraft
    {
        SpawnObjectsManager::SpawnObjectsManager()
        : map(nullptr)
        , currentIndex(0)
        , waitingForTransition(false)
        , transitionStarted(false)
        {
        }
        
        void SpawnObjectsManager::setMap(Map* map)
        {
            this->map = map;
            
            map->getMapTransitionController()->getTransitionFinishedSignal().Connect(this, &SpawnObjectsManager::onTransitionControllerFinished);
        }
        
        void SpawnObjectsManager::loadSquadsListFromFile(const std::string& filename)
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
        
        void SpawnObjectsManager::setPowerUpNames(const std::vector<std::string>& names)
        {
            powerUpNames = names;
        }
        
        void SpawnObjectsManager::loadSpawnEventsFromFile(const std::string& filename)
        {
            std::string fileContents = cocos2d::FileUtils::getInstance()->getStringFromFile(filename);
            
            Json::Reader reader;
            Json::Value json;
            reader.parse(fileContents, json);
            
            const auto& eventsJson = json["obj"];
            for (const auto& eventJson : eventsJson)
            {
                SpawnData data;
                data.time = eventJson["time"].asFloat();
                data.type = (SpawnObjectsType)eventJson["type"].asInt();
                data.templateName = eventJson["template"].asString();
                
                spawnItems.push_back(data);
            }
        }
        
        void SpawnObjectsManager::update(float dt)
        {
            CCASSERT(map != nullptr, "Map must be set before update is called");
            
            if (waitingForTransition)
            {
                map->getTime()->clearStage();
                if (!transitionStarted)
                {
                    if (!map->isAnyObjectPassingFilter(MapObjectInspector::isEnemy))
                    {
                        map->getMapTransitionController()->startTransition();
                        transitionStarted = true;
                    }
                    return;
                }
                else
                {
                    if (map->getMapTransitionController()->isTransitioning())
                    {
                        return;
                    }
                }
            }
            
            bool keepSpawning = (currentIndex < (int)spawnItems.size());
            while (keepSpawning)
            {
                float time = map->getTime()->getStageTime();
                const auto& nextSpawnItem = *(spawnItems.begin() + currentIndex);
                if (nextSpawnItem.time <= time)
                {
                    spawnItem(nextSpawnItem);
                    ++currentIndex;
                    keepSpawning = (currentIndex < (int)spawnItems.size());
                }
                else
                {
                    keepSpawning = false;
                }
            }
        }
        
        Gallant::Signal2<SpawnObjectsManager*, SpawnObjectsType>& SpawnObjectsManager::getSpawnSignal()
        {
            return spawnSignal;
        }
        
        void SpawnObjectsManager::spawnItem(const SpawnObjectsManager::SpawnData &data)
        {
            switch (data.type)
            {
                case SpawnObjectsType::eSquads:
                    spawnSquad(data.templateName);
                    break;
                case SpawnObjectsType::ePowerUps:
                    spawnPowerup(data.templateName);
                    break;
                case SpawnObjectsType::eTransitionStage:
                    transitionStage();
                    break;
                case SpawnObjectsType::eUpdateSpeed:
                    break;
                default:
                    break;
            }
        }
        
        void SpawnObjectsManager::spawnPowerup(const std::string &templateName) const
        {
            if (auto powerup = map->getFactory()->createObject(templateName))
            {
                float posX = map->getDefinition().screenSize.width * 0.5f;
                float posY = map->getDefinition().screenSize.height + 50.0f;
                powerup->getOrCreate<PositionComponent>()->setPosition(cocos2d::Vec2(posX, posY));
                map->addObject(powerup);
            }
            else
            {
                CCASSERT(false, "Powerup not found");
            }
        }
        
        void SpawnObjectsManager::spawnSquad(const std::string &templateName) const
        {
            const cocos2d::Size& screenSize = map->getDefinition().screenSize;
            cocos2d::Vec2 offset(screenSize.width * 0.5f, screenSize.height);
            
            const SquadTemplate* squadTemplate = getSquadTemplateWithName(templateName);
            if (!squadTemplate)
            {
                std::string assertStr = "Squad template not found: " + templateName;
                CCASSERT(squadTemplate != nullptr, assertStr.c_str());
                return;
            }
            
            std::vector<MapObject*> enemies;
            createSquad(*squadTemplate, offset, enemies);
            
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
        }
        
        void SpawnObjectsManager::transitionStage()
        {
            waitingForTransition = true;
            transitionStarted = false;
            if (!map->isAnyObjectPassingFilter(MapObjectInspector::isEnemy))
            {
                transitionStarted = true;
                map->getMapTransitionController()->startTransition();
            }
            map->getTime()->clearStage();
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
        
        void SpawnObjectsManager::createSquad(const SquadTemplate& squadTemplate, const cocos2d::Vec2& offset, std::vector<MapObject*>& enemies) const
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
        
        void SpawnObjectsManager::onTransitionControllerFinished(MapTransitionController* transitionController)
        {
            waitingForTransition = false;
        }
    }
}