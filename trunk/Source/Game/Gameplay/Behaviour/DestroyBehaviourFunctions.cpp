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
            bool isDead(MapObject* object)
            {
                return false;
            }
            
            bool isOutOfScreenDown(MapObject* object)
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
                            screenPos.y += viewComponent->getSize().height*0.5f;
                            
                            inside = (screenPos.y >= 0.0f);
                        }
                    }
                }
                return !inside;
            }
            
            bool isOutOfScreenUp(MapObject* object)
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
                            screenPos.y -= (viewComponent->getSize().height * 0.5f);
                            inside = (screenPos.y <= screenSize.height);
                        }
                    }
                }
                return !inside;
            }
            
            bool isCollision(MapObject* object)
            {
                auto collisionComponent = object->get<CollisionDetectionComponent>();
                return (collisionComponent && collisionComponent->getObject() && collisionComponent->hasCollision());
            }
        }
    }
}