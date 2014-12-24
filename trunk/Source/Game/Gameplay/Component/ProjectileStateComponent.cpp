//
//  ProjectileStateComponent.cpp
//  KillyCraft
//
//  Created by Ricard Perez del Campo on 24/12/14.
//  Copyright (c) 2014 MelonGames. All rights reserved.
//

#include "ProjectileStateComponent.h"
#include "Gameplay/MapObject.h"
#include "Gameplay/Map.h"
#include "CollisionDetectionComponent.h"

namespace MelonGames
{
    namespace KillyCraft
    {
        ProjectileStateComponent::ProjectileStateComponent()
        : livesCost(0)
        , nCollisionsSupported(0)
        , nCollisionsHappened(0)
        {
        }
        
        void ProjectileStateComponent::onObjectAttachedToMap()
        {
            Base::onObjectAttachedToMap();
            
            if (auto collisionDetection = object->get<CollisionDetectionComponent>())
            {
                collisionDetection->getCollisionSignal().Connect(this, &ProjectileStateComponent::onCollision);
            }
        }
        
        void ProjectileStateComponent::onWillDetachFromObject()
        {
            if (auto collisionDetection = object->get<CollisionDetectionComponent>())
            {
                collisionDetection->getCollisionSignal().Disconnect(this, &ProjectileStateComponent::onCollision);
            }
            Base::onWillDetachFromObject();
        }
        
        unsigned int ProjectileStateComponent::getLivesCost() const
        {
            return livesCost;
        }
        
        void ProjectileStateComponent::onCollision(CollisionDetectionComponent* first, CollisionDetectionComponent* second)
        {
            assert(first->getObject() == object);
            
            first->ignoreCollisionsAgainstObject(second->getObject());
            second->ignoreCollisionsAgainstObject(object);
            
            nCollisionsHappened++;
            if (nCollisionsHappened >= nCollisionsSupported)
            {
                object->getMap()->removeObjectWhenPossible(object);
            }
        }
    }
}