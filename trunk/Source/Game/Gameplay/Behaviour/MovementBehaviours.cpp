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
            auto moveState = object->getOrCreate<LinearMoveStateComponent>();
            posComponent->setPosition(posComponent->getPosition() + moveState->getMovementPerSecond()*dt);
        }
        
        
#pragma mark - MoveCircularBehaviour
        void MoveCircularBehaviour::update(MapObject *object, float dt)
        {
            Base::update(object, dt);
            
            auto moveState = object->getOrCreate<CircularMoveStateComponent>();
            
            float time = object->getOrCreate<TimeComponent>()->getTime();
            float lastTime = std::max(0.0f, time-dt);
            
            float radius = moveState->getRadius();
            float radiansPerSecond = moveState->getRadiansPerSecond();
            
            float moveX = radius * (std::cos(radiansPerSecond*time) - std::cos(radiansPerSecond*(lastTime)));
            float moveY = radius * (std::sin(radiansPerSecond*time) - std::sin(radiansPerSecond*(lastTime)));
            
            auto posComp = object->get<PositionComponent>();
            cocos2d::Vec3 position = posComp->getPosition();
            position.x += moveX;
            position.y += moveY;
            posComp->setPosition(position);
        }
    }
}