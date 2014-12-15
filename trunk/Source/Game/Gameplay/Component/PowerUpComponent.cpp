//
//  PowerUpComponent.cpp
//  KillyCraft
//
//  Created by Ricard Perez del Campo on 14/12/14.
//  Copyright (c) 2014 MelonGames. All rights reserved.
//

#include "PowerUpComponent.h"
#include "CollisionDetectionComponent.h"
#include "Gameplay/PowerUp/PowerUp.h"
#include "Gameplay/MapObject.h"

namespace MelonGames
{
    namespace KillyCraft
    {
        PowerUpComponent::PowerUpComponent()
        : applied(false)
        {
        }
        
        void PowerUpComponent::onObjectAttachedToMap()
        {
            Base::onObjectAttachedToMap();
            
            if (auto collisionDetection = object->get<CollisionDetectionComponent>())
            {
                collisionDetection->getCollisionSignal().Connect(this, &PowerUpComponent::onCollisionDetection);
            }
        }
        
        void PowerUpComponent::onWillDetachFromObject()
        {
            if (auto collisionDetection = object->get<CollisionDetectionComponent>())
            {
                collisionDetection->getCollisionSignal().Disconnect(this, &PowerUpComponent::onCollisionDetection);
            }
            
            Base::onWillDetachFromObject();
        }
        
        void PowerUpComponent::addPowerUp(const PowerUp *powerUp)
        {
            powerUps.push_back(powerUp);
        }
        
        void PowerUpComponent::onCollisionDetection(CollisionDetectionComponent* otherCollisionComponent)
        {
            assert(!applied && "Can apply only once");
            if (!applied)
            {
                applied = true;
                for (const auto& powerUp : powerUps)
                {
                    powerUp->applyToObject(otherCollisionComponent->getObject());
                }
            }
        }
    }
}