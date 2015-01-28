//
//  SpawnChildrenBehaviour.cpp
//  KillyCraft
//
//  Created by Ricard Perez del Campo on 28/01/15.
//  Copyright (c) 2015 MelonGames. All rights reserved.
//

#include "SpawnChildrenBehaviour.h"
#include "Gameplay/MapObject.h"
#include "Gameplay/Map.h"
#include "Gameplay/MapObjectsFactory.h"
#include "Gameplay/Component/PositionComponent.h"

namespace MelonGames
{
    namespace KillyCraft
    {
        SpawnChildrenBehaviour::SpawnChildrenBehaviour(const std::vector<std::string>& childrenTypes)
        : childrenTypes(childrenTypes)
        {
        }
        
        void SpawnChildrenBehaviour::update(MapObject* object, float dt)
        {
            Base::update(object, dt);
            
            cocos2d::Vec3 position;
            if (auto positionComponent = object->get<PositionComponent>())
            {
                position = positionComponent->getPosition();
            }
            
            Map* map = object->getMap();
            
            for (const std::string& childType : childrenTypes)
            {
                if (auto child = map->getFactory()->createObject(childType))
                {
                    if (auto positionComponent = child->get<PositionComponent>())
                    {
                        positionComponent->setPosition(position);
                    }
                    
                    map->addObject(child);
                }
            }
        }
    }
}