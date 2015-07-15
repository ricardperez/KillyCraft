//
//  Map.cpp
//  KillyCraft
//
//  Created by Ricard Pérez del Campo on 16/10/14.
//
//

#include "Map.h"
#include "Player.h"
#include "SpawnObjectsManager.h"
#include "MapObjectsFactory.h"
#include "MapTransitionController.h"
#include "VFXController.h"
#include "MapTime.h"
#include "MapObject.h"
#include "MapObjectInspector.h"
#include "View/MapView.h"
#include "Gamepad.h"
#include "GameConfig.h"
#include "MelonGames/Random.h"

#include "Component/Component.h"
#include "Component/ViewComponent.h"
#include "Component/PositionComponent.h"

#include "base/CCDirector.h"
#ifdef USE_GAMEPAD_SHOOT_BUTTON
#include "extensions/GUI/CCControlExtension/CCControlButton.h"
#endif

#include <cassert>

namespace MelonGames
{
	namespace KillyCraft
	{
		Map::Map(const MapDefinition& mapDefinition)
		: definition(mapDefinition)
        , node(nullptr)
        , view(nullptr)
		, player(nullptr)
        , spawnObjectsManager(nullptr)
        , factory(nullptr)
        , mapTransitionController(nullptr)
        , vfxController(nullptr)
        , time(nullptr)
        , nextIdentifier(0)
        , updating(false)
		{
		}
		
		Map::~Map()
		{
            for (auto object : objects)
            {
                delete object;
            }
            
            delete player;
            delete view;
            delete spawnObjectsManager;
            delete factory;
            delete mapTransitionController;
            delete vfxController;
            delete time;
		}
		
		void Map::setNode(cocos2d::Node *node)
		{
			this->node = node;
		}
		
        MapView* Map::getView() const
		{
			return view;
		}
		
		void Map::initialize()
		{
			assert(node);
            
            time = new MapTime();
            mapTransitionController = new MapTransitionController(this);
            
            player = new Player();
            player->addLives(10);
            
            factory = new MapObjectsFactory();
            factory->addTemplatesFromFile("Enemies.obj");
            factory->addTemplatesFromFile("Weapons.obj");
            factory->addTemplatesFromFile("PowerUps.obj");
            factory->addTemplatesFromFile("Player.obj");
            
            auto playerObject = factory->createObject("Player");
            PositionComponent* posComponent = playerObject->get<PositionComponent>();
            posComponent->setPosition(cocos2d::Vec2(150.0f, 130.0f));
            player->setPlayerObject(playerObject);
            
            view = new MapView(this, node);
            
            addObject(playerObject);
            
#ifdef USE_GAMEPAD_SHOOT_BUTTON
            auto shootingButton = player->getGamepad()->createShootingButton();
            node->addChild(shootingButton);
            shootingButton->setPosition(cocos2d::Point(node->getContentSize().width - shootingButton->getContentSize().width*0.5f - 50.0f, shootingButton->getContentSize().height*0.5f + 50.0f));
#endif
			
			spawnObjectsManager = new SpawnObjectsManager();
            spawnObjectsManager->setMap(this);
            spawnObjectsManager->loadSquadsListFromFile("Squads.kc");
            spawnObjectsManager->loadSpawnEventsFromFile("levels/Level1.kc");
            spawnObjectsManager->setPowerUpNames(factory->getObjectsNamesForFile("PowerUps.obj"));
            
            vfxController = new VFXController(this);
		}
        
        const MapDefinition& Map::getDefinition() const
        {
            return definition;
        }
		
		Player* Map::getPlayer() const
		{
			return player;
		}
        
        MapObjectsFactory* Map::getFactory() const
        {
            return factory;
        }
        
        MapTransitionController* Map::getMapTransitionController() const
        {
            return mapTransitionController;
        }
        
        VFXController* Map::getVFXController() const
        {
            return vfxController;
        }
        
        MapTime* Map::getTime() const
        {
            return time;
        }
		
		void Map::addObject(MapObject* o)
		{
            o->setIdentifier(nextIdentifier++);
            objects.push_back(o);
            o->onAttachedToMap(this);
		}
		
		void Map::removeObjectWhenPossible(MapObject* o)
		{
            if (updating)
            {
                if (std::find(objectsToRemove.begin(), objectsToRemove.end(), o) == objectsToRemove.end())
                {
                    objectsToRemove.push_back(o);
                }
            }
            else
            {
                o->onWillDetachFromMap();
                objects.erase(std::find(objects.begin(), objects.end(), o));
                delete o;
            }
		}
		
		void Map::update(float dt)
		{
            assert(view);
            
            updating = true;
            
            time->addTime(cocos2d::Director::getInstance()->getAnimationInterval());
            dt = time->getLastDt();
            
            view->update(dt);
            
            auto objectsCp = objects; //because we can be adding elements to the original vector while updating them...
            
            for (auto object : objectsCp)
            {
                assert(object->isValid());
                object->preupdate();
			}
			
			for (auto object : objectsCp)
			{
				object->update(dt);
			}
            
            for (auto object : objectsCp)
            {
                object->postupdate();
            }
            
            spawnObjectsManager->update(dt);
            mapTransitionController->update(dt);
            updating = false;
            
            for (auto object : objectsToRemove)
            {
                removeObjectWhenPossible(object);
            }
            objectsToRemove.clear();
		}
        
        const std::vector<MapObject*>& Map::getObjects() const
        {
            return objects;
        }
        
        std::vector<MapObject*> Map::getObjectsPassingFilter(const ObjectsFilter& filter) const
        {
            std::vector<MapObject*> result;
            for (auto object : objects)
            {
                if (filter(object))
                {
                    result.push_back(object);
                }
            }
            return result;
        }
        
        MapObject* Map::getObjectPassingFilter(const ObjectsFilter& filter) const
        {
            for (auto object : objects)
            {
                if (filter(object))
                {
                    return object;
                }
            }
            return nullptr;
        }
        
        bool Map::isAnyObjectPassingFilter(const ObjectsFilter& filter) const
        {
            for (auto object : objects)
            {
                if (filter(object))
                {
                    return true;
                }
            }
            return false;
        }
	}
}