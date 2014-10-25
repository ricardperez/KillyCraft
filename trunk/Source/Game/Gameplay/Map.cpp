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

#include "ObjectsFastFactory.h"

#include <cassert>

namespace MelonGames
{
	namespace KillyCraft
	{
		Map::Map()
		: node(nullptr)
		, player(nullptr)
		{
		}
		
		Map::~Map()
		{
			delete player;
		}
		
		void Map::setNode(cocos2d::Node *node)
		{
			this->node = node;
		}
		
		cocos2d::Node* Map::getNode() const
		{
			return node;
		}
		
		void Map::initialize()
		{
			assert(node);
			
			player = new Player();
			
			auto player = ObjectsFastFactory::createPlayerObject();
			addObject(player);
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