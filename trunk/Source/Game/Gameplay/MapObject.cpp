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
        , updating(false)
        , callWillDetachAfterUpdate(false)
        , identifier(0)
		{
		}
		
		MapObject::~MapObject()
		{
            auto it = components.begin();
            while (it != components.end())
            {
                auto component = *it;
                it = components.erase(it);
                delete component;
            }
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
			
            if (updating)
            {
                callWillDetachAfterUpdate = true;
            }
            else
            {
                for (auto& component : components)
                {
                    component->onWillDetachFromObject();
                }
                
                this->map = nullptr;
            }
		}
		
		bool MapObject::isValid() const
		{
			return valid;
		}
		
		Map* MapObject::getMap() const
		{
			return map;
		}
		
        void MapObject::preupdate()
        {
            assert(valid);
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
            
            for (auto component : components)
            {
                component->preupdate();
            }
        }
        
		void MapObject::update(float dt)
		{
			assert(valid);
            
            updating = true;
			
			for (auto component : components)
			{
				component->update(dt);
			}
            
            updating = false;
            
            if (callWillDetachAfterUpdate)
            {
                onWillDetachFromMap();
            }
		}
        
        int MapObject::getIdentifier() const
        {
            return identifier;
        }
        
        void MapObject::setIdentifier(int identifier)
        {
            this->identifier = identifier;
        }
	}
}