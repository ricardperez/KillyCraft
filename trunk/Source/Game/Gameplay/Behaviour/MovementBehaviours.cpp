//
//  MovementBehaviours.cpp
//  KillyCraft
//
//  Created by Ricard Perez del Campo on 31/10/14.
//  Copyright (c) 2014 MelonGames. All rights reserved.
//

#include "MovementBehaviours.h"
#include "Gameplay/MapObject.h"
#include "Gameplay/Component/MovementStateComponents.h"
#include "Gameplay/Component/PositionComponent.h"
#include "Gameplay/Component/TimeComponent.h"
#include <cmath>

namespace MelonGames
{
    namespace KillyCraft
    {
#pragma mark - MoveLinearBehaviour
        void MoveLinearBehaviour::update(MapObject* object, float dt)
        {
            Base::update(object, dt);
            
            auto posComponent = object->getOrCreate<PositionComponent>();
            auto moveState = object->getOrCreate<MoveLinearStateComponent>();
            posComponent->setPosition(posComponent->getPosition() + moveState->getMovementPerSecond()*dt);
        }
        
        
#pragma mark - MoveCircularBehaviour
        void MoveCircularBehaviour::update(MapObject *object, float dt)
        {
            Base::update(object, dt);
            
            auto moveState = object->getOrCreate<MoveCircularStateComponent>();
            
            float time = object->getOrCreate<TimeComponent>()->getTime();
            float lastTime = std::max(0.0f, time-dt);
            
            float radius = moveState->getRadius();
            float radiansPerSecond = moveState->getRadiansPerSecond();
            
            float moveX = radius * (std::cos(radiansPerSecond*time) - std::cos(radiansPerSecond*(lastTime)));
            float moveY = radius * (std::sin(radiansPerSecond*time) - std::sin(radiansPerSecond*(lastTime)));
            object->get<PositionComponent>()->movePosition(cocos2d::Vec2(moveX, moveY));
        }
        
#pragma mark - MoveCircularProjectedBehaviour
        void MoveCircularProjectedBehaviour::update(MapObject* object, float dt)
        {
            Base::update(object, dt);
            
            auto moveState = object->getOrCreate<MoveCircularStateComponent>();
            
            float time = object->getOrCreate<TimeComponent>()->getTime();
            float lastTime = std::max(0.0f, time-dt);
            
            float radius = moveState->getRadius();
            float radiansPerSecond = moveState->getRadiansPerSecond();
            
            float moveX = radius * (std::cos(radiansPerSecond*time) - std::cos(radiansPerSecond*(lastTime)));
            object->get<PositionComponent>()->movePositionX(moveX);
        }
    }
}