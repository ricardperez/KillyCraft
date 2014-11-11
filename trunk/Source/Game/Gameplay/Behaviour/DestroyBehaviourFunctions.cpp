//
//  DestroyBehaviourFunctions.cpp
//  KillyCraft
//
//  Created by Ricard Perez del Campo on 31/10/14.
//  Copyright (c) 2014 MelonGames. All rights reserved.
//

#include "DestroyBehaviourFunctions.h"
#include "DestroyBehaviour.h"
#include "Gameplay/Map.h"
#include "Gameplay/MapObject.h"
#include "Gameplay/Component/ViewComponent.h"
#include "Gameplay/Component/PositionComponent.h"
#include "Gameplay/Component/CollisionDetectionComponent.h"
#include "2d/CCSprite.h"

namespace MelonGames
{
    namespace KillyCraft
    {
        namespace DestroyBehaviourFunctions
        {
            DestroyCheckFunction makeIsDeadFunction()
            {
                return [](MapObject* object) -> bool
                {
                    return false;
                };
            }
            DestroyCheckFunction makeIsOutOfScreenDownFunction()
            {
                return [](MapObject* object) -> bool
                {
                    bool inside = false;
                    if (auto positionComponent = object->get<PositionComponent>())
                    {
                        cocos2d::Vec2 screenPos = Perspective::screenPosition(positionComponent->getPosition());
                        inside = (screenPos.y >= 0.0f);
                        if (!inside)
                        {
                            if (auto viewComponent = object->get<ViewComponent>())
                            {
                                if (auto sprite = viewComponent->getSprite())
                                {
                                    cocos2d::Size spriteSize = (sprite->getContentSize() * sprite->getScale());
                                    screenPos.y += spriteSize.height*0.5f;
                                    
                                    inside = (screenPos.y >= 0.0f);
                                }
                            }
                        }
                    }
                    return !inside;
                };
            }
            
            DestroyCheckFunction makeIsOutOfScreenUpFunction()
            {
                return [](MapObject* object) -> bool
                {
                    bool inside = false;
                    if (auto positionComponent = object->get<PositionComponent>())
                    {
                        cocos2d::Size screenSize = object->getMap()->getDefinition().screenSize;
                        cocos2d::Vec2 screenPos = Perspective::screenPosition(positionComponent->getPosition());
                        inside = (screenPos.y <= screenSize.height);
                        if (!inside)
                        {
                            if (auto viewComponent = object->get<ViewComponent>())
                            {
                                if (auto sprite = viewComponent->getSprite())
                                {
                                    cocos2d::Size spriteSize = (sprite->getContentSize() * sprite->getScale());
                                    screenPos.y -= spriteSize.height*0.5f;
                                    
                                    inside = (screenPos.y <= screenSize.height);
                                }
                            }
                        }
                    }
                    return !inside;
                };
            }
            
            DestroyCheckFunction makeIsCollisionFunction()
            {
                return [](MapObject* object) -> bool
                {
                    auto collisionComponent = object->get<CollisionDetectionComponent>();
                    if (collisionComponent && collisionComponent->getObject())
                    {
                        const auto& objects = object->getMap()->getObjects();
                        for (auto other : objects)
                        {
                            if (other != object)
                            {
                                auto otherCollisionComponent = other->get<CollisionDetectionComponent>();
                                if (otherCollisionComponent && otherCollisionComponent->getObject())
                                {
                                    if (collisionComponent->collidesAgainst(otherCollisionComponent))
                                    {
                                        return true;
                                    }
                                }
                            }
                        }
                    }
                    
                    return false;
                };
            }
        }
    }
}