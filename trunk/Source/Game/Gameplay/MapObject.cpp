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
			components.clear();
		}
		
		void MapObject::addComponent(Component* component)
		{
			if (map)
			{
				componentsToAdd.emplace_back(component);
			}
			else
			{
				components.emplace_back(component);
				component->onAttachedToObject(this);
			}
		}
		
		void MapObject::removeComponent(Component *component)
		{
			if (component)
			{
				component->onWillDetachFromObject();
				componentsToRemove.push_back(component);
			}
		}
		
		void MapObject::flush()
		{
			assert(map);
			
			for (auto component : componentsToRemove)
			{
				auto it = std::find(components.begin(), components.end(), component);
				if (it != components.end())
				{
					components.erase(it);
				}
			}
			componentsToRemove.clear();
			
			for (auto component : componentsToAdd)
			{
				components.emplace_back(component);
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