//
//  PlayerLivesControllerComponent.cpp
//  KillyCraft
//
//  Created by Ricard Perez del Campo on 23/12/14.
//  Copyright (c) 2014 MelonGames. All rights reserved.
//

#include "PlayerLivesControllerComponent.h"
#include "CollisionDetectionComponent.h"
#include "EnemyStateComponent.h"
#include "Gameplay/MapObject.h"
#include "Gameplay/Map.h"
#include "Gameplay/Player.h"
#include "Gameplay/MapObjectInspector.h"

namespace MelonGames
{
    namespace KillyCraft
    {
        void PlayerLivesControllerComponent::onObjectAttachedToMap()
        {
            Base::onObjectAttachedToMap();
            
            if (auto collisionDetection = object->get<CollisionDetectionComponent>())
            {
                collisionDetection->getCollisionSignal().Connect(Gallant::MakeDelegate(this, &PlayerLivesControllerComponent::onPlayerCollision));
            }
        }
        
        void PlayerLivesControllerComponent::onWillDetachFromObject()
        {
            if (auto collisionDetection = object->get<CollisionDetectionComponent>())
            {
                collisionDetection->getCollisionSignal().Disconnect(Gallant::MakeDelegate(this, &PlayerLivesControllerComponent::onPlayerCollision));
            }
            Base::onWillDetachFromObject();
        }
        
        void PlayerLivesControllerComponent::onPlayerCollision(CollisionDetectionComponent* playerCollisionDetection, CollisionDetectionComponent* otherCollisionDetection)
        {
            auto otherObject = otherCollisionDetection->getObject();
            if (MapObjectInspector::isEnemy(otherObject))
            {
                auto enemyState = otherObject->get<EnemyStateComponent>();
                object->getMap()->getPlayer()->removeLives(enemyState->getLivesCost());
            }
        }
    }
}