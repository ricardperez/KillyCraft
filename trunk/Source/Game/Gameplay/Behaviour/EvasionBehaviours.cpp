//
//  EvasionBehaviours.cpp
//  KillyCraft
//
//  Created by Ricard Perez del Campo on 20/01/15.
//  Copyright (c) 2015 MelonGames. All rights reserved.
//

#include "EvasionBehaviours.h"
#include "MoveActions.h"
#include "Gameplay/MapObject.h"
#include "Gameplay/Map.h"
#include "Gameplay/MapObjectInspector.h"
#include "Gameplay/Component/PositionComponent.h"
#include "Gameplay/Component/ViewComponent.h"
#include "Gameplay/Component/MovementStateComponents.h"
#include "2d/CCSprite.h"

namespace MelonGames
{
    namespace KillyCraft
    {
        void EvadeProjectilesHorizontally::update(MapObject* object, float dt)
        {
            if (auto posComponent = object->get<PositionComponent>())
            {
                float allowedDistance = 350.0f;
                if (auto viewComponent = object->get<ViewComponent>())
                {
                    allowedDistance += viewComponent->getSize().width * 0.5f;
                }
                
                const cocos2d::Vec2& position = posComponent->getPosition();
                
                MapObject* closestProjectile = nullptr;
                float closestDistSq = std::numeric_limits<float>::max();
                
                const std::vector<MapObject*>& allObjects = object->getMap()->getObjects();
                for (auto mapObject : allObjects)
                {
                    if (MapObjectInspector::isProjectile(mapObject))
                    {
                        if (auto projectilePosComponent = mapObject->get<PositionComponent>())
                        {
                            const cocos2d::Vec2& projectilePosition = projectilePosComponent->getPosition();
                            if (projectilePosition.y < position.y)
                            {
                                float distanceSq = projectilePosition.distanceSquared(position);
                                if (distanceSq < closestDistSq)
                                {
                                    closestDistSq = distanceSq;
                                    closestProjectile = mapObject;
                                }
                            }
                        }
                    }
                }
                
                if (closestProjectile)
                {
                    if (closestDistSq < allowedDistance*allowedDistance)
                    {
                        const cocos2d::Vec2& projectilePosition = closestProjectile->get<PositionComponent>()->getPosition();
                        
                        if (auto moveStateComponent = object->get<MoveLinearStateComponent>())
                        {
                            float speed = moveStateComponent->getMovementPerSecond().x;
                            float distance = ((projectilePosition.x > position.x) ? -speed*dt : speed*dt);
                            MoveActions::moveOnX(object, distance);
                        }
                    }
                    
                    
                }
            }
        }
    }
}