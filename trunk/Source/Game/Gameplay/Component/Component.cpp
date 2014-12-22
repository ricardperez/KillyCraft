//
//  Component.cpp
//  KillyCraft
//
//  Created by Ricard Pérez del Campo on 16/10/14.
//
//

#include "Component.h"
#include "Gameplay/MapObject.h"
#include <cassert>

namespace MelonGames
{
	namespace KillyCraft
	{
		Component::Component()
		: object(nullptr)
		{
			
		}
		
		Component::~Component()
		{
		}
		
		void Component::onAttachedToObject(MapObject *o)
		{
			assert(object == nullptr && "A component must be attached once and only once");
			assert(o != nullptr && "A component can't be attached to a null object");
			
			object = o;
		}
		
		void Component::onObjectAttachedToMap()
		{
			
		}
		
		void Component::onWillDetachFromObject()
		{
			object = nullptr;
		}
        
        void Component::preupdate()
        {
        }
        
        void Component::postupdate()
        {
        }
		
		void Component::update(float dt)
		{
		}
        
        MapObject* Component::getObject() const
        {
            return object;
        }
	}
}
