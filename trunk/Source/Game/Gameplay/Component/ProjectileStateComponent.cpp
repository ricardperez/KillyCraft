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
#include "Gameplay/MapObjectInspector.h"
#include "Gameplay/Player.h"
#include "CollisionDetectionComponent.h"
#include "EnemyStateComponent.h"

namespace MelonGames
{
    namespace KillyCraft
    {
        ProjectileStateComponent::ProjectileStateComponent()
        : power(0)
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
        
        unsigned int ProjectileStateComponent::getPower() const
        {
            return power;
        }
        
        void ProjectileStateComponent::onCollision(CollisionDetectionComponent* first, CollisionDetectionComponent* second)
        {
            assert(first->getObject() == object);
            
            first->ignoreCollisionsAgainstObject(second->getObject());
            second->ignoreCollisionsAgainstObject(object);
            
            nCollisionsHappened++;
            if (nCollisionsHappened >= nCollisionsSupported)
            {
                if (auto enemyState = second->getObject()->get<EnemyStateComponent>())
                {
                    object->getMap()->getPlayer()->addScore(enemyState->getScore());
                }
                
                object->getMap()->removeObjectWhenPossible(object);
            }
        }
    }
}