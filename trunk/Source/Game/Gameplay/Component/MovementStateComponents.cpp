//
//  MovementStateComponents.cpp
//  KillyCraft
//
//  Created by Ricard Perez del Campo on 31/10/14.
//  Copyright (c) 2014 MelonGames. All rights reserved.
//

#include "MovementStateComponents.h"
#include "Gameplay/MapObject.h"
#include "Gameplay/Map.h"
#include "Gameplay/MapTime.h"
#include "Gameplay/MapTransitionController.h"
#include "GamepadComponent.h"
#include <cmath>

namespace MelonGames
{
    namespace KillyCraft
    {
#pragma mark - MoveLinearStateComponent
        MoveLinearStateComponent::MoveLinearStateComponent()
        : backgroundSpeedMultiplier(0.0f)
        {
            
        }
        
        const cocos2d::Vec2& MoveLinearStateComponent::getMovementPerSecond() const
        {
            return movementPerSecond;
        }
        
        void MoveLinearStateComponent::setMovementPerSecond(const cocos2d::Vec2& movementPerSecond)
        {
            this->movementPerSecond = movementPerSecond;
        }
        
        float MoveLinearStateComponent::getBackgroundSpeedMultiplier() const
        {
            return backgroundSpeedMultiplier;
        }
        
        void MoveLinearStateComponent::setBackgroundSpeedMultiplier(float backgroundSpeedMultiplier)
        {
            this->backgroundSpeedMultiplier = backgroundSpeedMultiplier;
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
        
#pragma mark - MoveIdleStateComponent
        MoveIdleStateComponent::MoveIdleStateComponent()
        : movementDistanceX(0.0f)
        , movementDistanceY(0.0f)
        , movementTime(0.0f)
        , gaussianA(0.0f)
        , gaussianC(0.0f)
        , gaussianXRange(0.0f)
        , time(0.0f)
        , prevTime(0.0f)
        , idleTime(0.0f)
        {
            
        }
        
        void MoveIdleStateComponent::update(float dt)
        {
            Base::update(dt);
            
            prevTime = time;
            
            bool moving  = false;
            if (auto gamepadComponent = object->get<GamepadComponent>())
            {
                moving = gamepadComponent->isMoving();
            }
            
            if (!moving)
            {
                moving = object->getMap()->getMapTransitionController()->isTransitioning();
            }
            
            if (!moving)
            {
                idleTime += dt;
                if (idleTime >= 1.0f)
                {
                    time += dt;
                }
            }
            else
            {
                idleTime = 0.0f;
            }
        }
        
        float MoveIdleStateComponent::getMovementDistanceX() const
        {
            return movementDistanceX;
        }
        
        float MoveIdleStateComponent::getMovementDistanceY() const
        {
            return movementDistanceY;
        }
        
        float MoveIdleStateComponent::getMovementTime() const
        {
            return movementTime;
        }
        
        float MoveIdleStateComponent::getGaussianA() const
        {
            return gaussianA;
        }
        
        float MoveIdleStateComponent::getGaussianC() const
        {
            return gaussianC;
        }
        
        float MoveIdleStateComponent::getGaussianXRange() const
        {
            return gaussianXRange;
        }
        
        float MoveIdleStateComponent::getTime() const
        {
            return time;
        }
        
        float MoveIdleStateComponent::getPreviousTime() const
        {
            return prevTime;
        }
    }
}