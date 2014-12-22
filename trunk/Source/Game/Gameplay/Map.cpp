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
#include "MapObject.h"
#include "Component/Component.h"
#include "Component/ViewComponent.h"
#include "View/MapView.h"
#include "Gamepad.h"
#include "ObjectsFastFactory.h"

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
        , elapsedTime(0.0f)
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
            
            view = new MapView(this, node);
			
			player = new Player();
            
#ifdef USE_GAMEPAD_SHOOT_BUTTON
            auto shootingButton = player->getGamepad()->createShootingButton();
            node->addChild(shootingButton);
            shootingButton->setPosition(cocos2d::Point(node->getContentSize().width - shootingButton->getContentSize().width*0.5f - 50.0f, shootingButton->getContentSize().height*0.5f + 50.0f));
#endif
			
			auto player = ObjectsFastFactory::createPlayerObject();
			addObject(player);
            
            factory = new MapObjectsFactory();
            factory->addTemplatesFromFile("Objects.obj");
            factory->addTemplatesFromFile("PowerUps.obj");
            
            spawnObjectsManager = new SpawnObjectsManager();
            spawnObjectsManager->setMap(this);
            spawnObjectsManager->loadEnemySquadsFromFile("Squads.squads");
            spawnObjectsManager->loadPowerUpsFromFile("PowerUps.list");
		}
        
        const MapDefinition& Map::getDefinition() const
        {
            return definition;
        }
		
		Player* Map::getPlayer() const
		{
			return player;
		}
		
		void Map::addObject(MapObject* o)
		{
            if (updating)
            {
                objectsToAdd.push_back(o);
            }
            else
            {
                o->setIdentifier(nextIdentifier++);
                objects.push_back(o);
                o->onAttachedToMap(this);
            }
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
            
            elapsedTime += dt;
            
            view->update(dt);
            
            for (auto object : objects)
            {
                assert(object->isValid());
                object->preupdate();
			}
			
			for (auto object : objects)
			{
				object->update(dt);
			}
            
            spawnObjectsManager->update(dt);
            
            updating = false;
            
            for (auto object : objectsToRemove)
            {
                removeObjectWhenPossible(object);
            }
            objectsToRemove.clear();
            
            for (auto object : objectsToAdd)
            {
                addObject(object);
            }
            objectsToAdd.clear();
		}
        
        float Map::getElapsedTime() const
        {
            return elapsedTime;
        }
        
        MapObjectsFactory* Map::getFactory() const
        {
            return factory;
        }
        
        const std::vector<MapObject*>& Map::getObjects() const
        {
            return objects;
        }
	}
}