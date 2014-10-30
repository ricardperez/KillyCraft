//
//  MapObject.cpp
//  KillyCraft
//
//  Created by Ricard Pérez del Campo on 16/10/14.
//
//

#include "MapObject.h"
#include <cassert>

namespace MelonGames
{
	namespace KillyCraft
	{
		MapObject::MapObject()
		: map(nullptr)
		, valid(false)
		{
		}
		
		MapObject::~MapObject()
		{
            for (auto it = components.begin(); it != components.end(); ++it)
            {
                delete *it;
            }
			components.clear();
		}
		
		void MapObject::addComponent(Component* component)
		{
			if (map)
			{
				componentsToAdd.push_back(component);
			}
			else
			{
				components.push_back(component);
				component->onAttachedToObject(this);
			}
		}
		
		void MapObject::removeComponent(Component *component)
		{
            component->onWillDetachFromObject();
            componentsToRemove.push_back(component);
		}
		
		void MapObject::flush()
		{
			assert(map);
			
			for (auto component : componentsToRemove)
			{
				auto it = std::find(components.begin(), components.end(), component);
                assert (it != components.end());
                components.erase(it);
                delete component;
			}
			componentsToRemove.clear();
			
			for (auto component : componentsToAdd)
			{
				components.push_back(component);
				component->onAttachedToObject(this);
				component->onObjectAttachedToMap();
			}
			componentsToAdd.clear();
		}
		
		
		void MapObject::onAttachedToMap(Map* map)
		{
			this->map = map;
			
			for (auto component : components)
			{
				component->onObjectAttachedToMap();
			}
			
			valid = true;
		}
		
		void MapObject::onWillDetachFromMap()
		{
			valid = false;
			
			for (auto& component : components)
			{
				component->onWillDetachFromObject();
			}
			
			this->map = nullptr;
		}
		
		bool MapObject::isValid() const
		{
			return valid;
		}
		
		Map* MapObject::getMap() const
		{
			return map;
		}
		
		void MapObject::update(float dt)
		{
			assert(valid);
			
			for (auto component : components)
			{
				component->update(dt);
			}
		}
	}
}