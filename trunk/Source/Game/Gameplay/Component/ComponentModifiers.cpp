//
//  ComponentModifiers.cpp
//  KillyCraft
//
//  Created by Ricard Perez del Campo on 31/10/14.
//  Copyright (c) 2014 MelonGames. All rights reserved.
//

#include "ComponentModifiers.h"
#include "Gameplay/MapObject.h"
#include "TimeComponent.h"
#include "MovementStateComponents.h"

namespace MelonGames
{
    namespace KillyCraft
    {
        namespace ComponentModifiers
        {
            ComponentModifier makeAccelerateLinearMovement(const cocos2d::Vec3& acceleration, float duration)
            {
                return [acceleration, duration](MapObject* object, float dt) -> void
                {
                    float time = object->getOrCreate<TimeComponent>()->getTime();
                    if (time < duration)
                    {
                        auto moveState = object->getOrCreate<LinearMoveStateComponent>();
                        moveState->setMovementPerSecond(moveState->getMovementPerSecond() + acceleration*dt);
                    }
                };
            }
            
            ComponentModifier makeAccelerateCircularMovement(float acceleration, float duration)
            {
                return [acceleration, duration](MapObject* object, float dt) -> void
                {
                    float time = object->getOrCreate<TimeComponent>()->getTime();
                    if (time < duration)
                    {
                        auto moveState = object->getOrCreate<CircularMoveStateComponent>();
                        moveState->setRadiansPerSecond(moveState->getRadiansPerSecond() + acceleration*dt);
                    }
                };
            }
            
            ComponentModifier makeChangeRadiusForCircularMovement(float maxRadius, float minRadius, float speed)
            {
                return [maxRadius, minRadius, speed](MapObject* object, float dt) -> void
                {
                    float dSpeed = speed*dt;
                    
                    float changeTime = (maxRadius - minRadius) / speed;
                    float livedTime = object->getOrCreate<TimeComponent>()->getTime();
                    
                    bool increase = (((int)(livedTime / changeTime) % 2) == 0);
                    
                    auto moveState = object->getOrCreate<CircularMoveStateComponent>();
                    float radius = std::min(maxRadius, std::max(minRadius, moveState->getRadius()));
                    radius += increase ? dSpeed : -dSpeed;
                    moveState->setRadius(radius);
                };
            }
        }
    }
}
