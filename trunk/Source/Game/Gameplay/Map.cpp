//
//  Map.cpp
//  KillyCraft
//
//  Created by Ricard Pérez del Campo on 16/10/14.
//
//

#include "Map.h"
#include "Player.h"
#include "MapObject.h"
#include "Component.h"
#include "ViewComponent.h"
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
		{
		}
		
		Map::~Map()
		{
            delete player;
            delete view;
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
					it = objects.erase(it);
				}
			}
			
			for (auto object : objects)
			{
				object->update(dt);
			}
		}
	}
}