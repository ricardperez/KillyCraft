//
//  PlayerStateComponent.cpp
//  KillyCraft
//
//  Created by Ricard Perez del Campo on 06/08/15.
//  Copyright (c) 2015 MelonGames. All rights reserved.
//

#include "PlayerStateComponent.h"
#include "CollisionDetectionComponent.h"
#include "EnemyStateComponent.h"
#include "PositionComponent.h"
#include "Gameplay/MapObject.h"
#include "Gameplay/Map.h"
#include "Gameplay/Player.h"
#include "Gameplay/MapObjectInspector.h"
#include "Gameplay/MapEvents.h"
#include "Gameplay/VFXController.h"

namespace MelonGames
{
    namespace KillyCraft
    {
        void PlayerStateComponent::onObjectAttachedToMap()
        {
            Base::onObjectAttachedToMap();
            
            if (auto collisionDetection = object->get<CollisionDetectionComponent>())
            {
                collisionDetection->getCollisionSignal().Connect(Gallant::MakeDelegate(this, &PlayerStateComponent::onPlayerCollision));
            }
            
            object->getMap()->getMapEvents()->getEnemyKilledSignal().Connect(this, &PlayerStateComponent::onEnemyKilled);
        }
        
        void PlayerStateComponent::onWillDetachFromObject()
        {
            if (auto collisionDetection = object->get<CollisionDetectionComponent>())
            {
                collisionDetection->getCollisionSignal().Disconnect(Gallant::MakeDelegate(this, &PlayerStateComponent::onPlayerCollision));
            }
            Base::onWillDetachFromObject();
        }
        
        void PlayerStateComponent::onPlayerCollision(CollisionDetectionComponent* playerCollisionDetection, CollisionDetectionComponent* otherCollisionDetection)
        {
            auto otherObject = otherCollisionDetection->getObject();
            if (MapObjectInspector::isEnemy(otherObject))
            {
                auto enemyState = otherObject->get<EnemyStateComponent>();
                enemyState->removeLives(enemyState->getLives());
                object->getMap()->getPlayer()->removeLives(enemyState->getLivesCost());
            }
        }
        
        void PlayerStateComponent::onEnemyKilled(MapObject* enemy)
        {
            auto enemyState = enemy->get<EnemyStateComponent>();
            object->getMap()->getPlayer()->addScore(enemyState->getScore());
            
            const cocos2d::Vec2& position = enemy->get<PositionComponent>()->getPosition();
            object->getMap()->getVFXController()->showScoreNode(enemyState->getScore(), cocos2d::Vec2(position.x, position.y), true);
        }
    }
}