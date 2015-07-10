//
//  MovementStateComponents.cpp
//  KillyCraft
//
//  Created by Ricard Perez del Campo on 31/10/14.
//  Copyright (c) 2014 MelonGames. All rights reserved.
//

#include "MovementStateComponents.h"
#include <cmath>

namespace MelonGames
{
    namespace KillyCraft
    {
#pragma mark - MoveLinearStateComponent
        const cocos2d::Vec2& MoveLinearStateComponent::getMovementPerSecond() const
        {
            return movementPerSecond;
        }
        
        void MoveLinearStateComponent::setMovementPerSecond(const cocos2d::Vec2& movementPerSecond)
        {
            this->movementPerSecond = movementPerSecond;
        }
        
#pragma mark - MoveCircularStateComponent
        MoveCircularStateComponent::MoveCircularStateComponent()
        : radiansPerSecond(0.0f)
        , radius(0.0f)
        {
        }
        
        float MoveCircularStateComponent::getRadiansPerSecond() const
        {
            return radiansPerSecond;
        }
        
        float MoveCircularStateComponent::getPeriod() const
        {
            return (radiansPerSecond / (M_PI * 2.0f));
        }
        
        void MoveCircularStateComponent::setRadiansPerSecond(float radsPerSec)
        {
            radiansPerSecond = radsPerSec;
        }
        
        void MoveCircularStateComponent::setPeriod(float period)
        {
            radiansPerSecond = (2.0f * M_PI / period);
        }
        
        float MoveCircularStateComponent::getRadius() const
        {
            return radius;
        }
        
        void MoveCircularStateComponent::setRadius(float rad)
        {
            radius = rad;
        }
    }
}