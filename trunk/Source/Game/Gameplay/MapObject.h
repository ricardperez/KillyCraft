//
//  MapObject.h
//  KillyCraft
//
//  Created by Ricard Pérez del Campo on 16/10/14.
//
//

#ifndef __KillyCraft__MapObject__
#define __KillyCraft__MapObject__

#include <vector>
#include "Component/Component.h"
#include "Component/ComponentModifiers.h"
#include <vector>

namespace MelonGames
{
	namespace KillyCraft
	{
		class Map;
        
        class MapObject
		{
		public:
			MapObject();
			virtual ~MapObject();
			
			void addComponent(Component* component);
			void removeComponent(Component* component);
			void flush();
            
            void addComponentModifier(const ComponentModifier& modifier);
			
			template <typename T>
			T* get() const;
            
            template <typename T>
            T* getOrCreate();
			
			void onAttachedToMap(Map* map);
			void onWillDetachFromMap();
			
			bool isValid() const;
			
			Map* getMap() const;
			
			void update(float dt);
			
		private:
			Map* map;
			std::vector<Component*> components;
			bool valid;
			
			std::vector<Component*> componentsToAdd;
			std::vector<Component*> componentsToRemove;
            
            
            std::vector<ComponentModifier> componentModifiers;
		};
		
		template <typename T>
		T* MapObject::get() const
		{
			for (auto c : components)
			{
				if (c->isA<T>())
				{
					return (T*)c;
				}
			}
            
			return nullptr;
		}
        
        template <typename T>
        T* MapObject::getOrCreate()
        {
            for (auto c : components)
            {
                if (c->isA<T>())
                {
                    return (T*)c;
                }
            }
            
            T* newInstance = new T();
            addComponent((Component*)newInstance);
            return newInstance;
        }
	}
}

#endif /* defined(__KillyCraft__MapObject__) */
