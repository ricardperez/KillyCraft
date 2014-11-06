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

#include "ObjectsFastFactory.h"

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
			
			auto player = ObjectsFastFactory::createPlayerObject();
			addObject(player);
            
            spawnObjectsManager = new SpawnObjectsManager();
            spawnObjectsManager->setMap(this);
            
            factory = new MapObjectsFactory();
            
            auto enemy = ObjectsFastFactory::createEnemyObject();
            addObject(enemy);
            
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
			objects.push_back(o);
			o->onAttachedToMap(this);
		}
		
		void Map::removeObjectWhenPossible(MapObject* o)
		{
			o->onWillDetachFromMap();
		}
		
		void Map::update(float dt)
		{
            assert(view);
            
            elapsedTime += dt;
            
            view->update(dt);
            
			auto it = objects.begin();
			while (it != objects.end())
			{
				MapObject* obj = *it;
				if (obj->isValid())
				{
					obj->flush();
					++it;
				}
				else
				{
                    MapObject* obj = *it;
					it = objects.erase(it);
                    delete obj;
				}
			}
			
			for (auto object : objects)
			{
				object->update(dt);
			}
            
            spawnObjectsManager->update(dt);
		}
        
        float Map::getElapsedTime() const
        {
            return elapsedTime;
        }
	}
}