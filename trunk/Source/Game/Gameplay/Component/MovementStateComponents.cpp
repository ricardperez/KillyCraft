//
//  MovementStateComponents.cpp
//  KillyCraft
//
//  Created by Ricard Perez del Campo on 31/10/14.
//  Copyright (c) 2014 MelonGames. All rights reserved.
//

#include "MovementStateComponents.h"

namespace MelonGames
{
    namespace KillyCraft
    {
#pragma mark - LinearMoveStateComponent
        const cocos2d::Vec3& LinearMoveStateComponent::getMovementPerSecond() const
        {
            return movementPerSecond;
        }
        
        void LinearMoveStateComponent::setMovementPerSecond(const cocos2d::Vec3& movementPerSecond)
        {
            this->movementPerSecond = movementPerSecond;
        }
        
#pragma mark - CircularMoveStateComponent
        CircularMoveStateComponent::CircularMoveStateComponent()
        : radiansPerSecond(0.0f)
        , radius(0.0f)
        {
        }
        
        float CircularMoveStateComponent::getRadiansPerSecond() const
        {
            return radiansPerSecond;
        }
        
        void CircularMoveStateComponent::setRadiansPerSecond(float radiansPerSecond)
        {
            this->radiansPerSecond = radiansPerSecond;
        }
        
        float CircularMoveStateComponent::getRadius() const
        {
            return radius;
        }
        
        void CircularMoveStateComponent::setRadius(float radius)
        {
            this->radius = radius;
        }
    }
}