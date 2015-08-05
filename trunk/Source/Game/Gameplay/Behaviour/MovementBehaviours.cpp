//
//  MovementBehaviours.cpp
//  KillyCraft
//
//  Created by Ricard Perez del Campo on 31/10/14.
//  Copyright (c) 2014 MelonGames. All rights reserved.
//

#include "MovementBehaviours.h"
#include "Gameplay/MapObject.h"
#include "Gameplay/Map.h"
#include "Gameplay/View/MapView.h"
#include "Gameplay/View/StarsView.h"
#include "Gameplay/Component/MovementStateComponents.h"
#include "Gameplay/Component/PositionComponent.h"
#include "Gameplay/Component/TimeComponent.h"
#include <cmath>

namespace MelonGames
{
    namespace KillyCraft
    {   
#pragma mark - MoveLinearBehaviour
        MoveLinearBehaviour::MoveLinearBehaviour()
        : projection(Projection::eNormal)
        {
        }
        
        void MoveLinearBehaviour::setProjection(MoveLinearBehaviour::Projection projection)
        {
            this->projection = projection;
        }
        
        void MoveLinearBehaviour::update(MapObject* object, float dt)
        {
            Base::update(object, dt);
            
            auto posComponent = object->getOrCreate<PositionComponent>();
            auto moveState = object->getOrCreate<MoveLinearStateComponent>();
            
            cocos2d::Vec2 addedSpeed = (object->getMap()->getView()->getStarsView()->getSpeedVector() * moveState->getBackgroundSpeedMultiplier());
            
            switch (projection)
            {
                case Projection::eNormal:
                default:
                    posComponent->movePosition((moveState->getMovementPerSecond() + addedSpeed) * dt);
                    break;
                case Projection::eHorizontal:
                    posComponent->movePositionX((moveState->getMovementPerSecond().x + addedSpeed.x) * dt);
                    break;
                case Projection::eVertical:
                    posComponent->movePositionY((moveState->getMovementPerSecond().y + addedSpeed.y) * dt);
                    break;
            }
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
            
            float moveX = radius * (std::cos(radiansPerSecond*time + M_PI_2) - std::cos(radiansPerSecond*lastTime + M_PI_2));
            object->get<PositionComponent>()->movePositionX(moveX);
        }
        
#pragma mark - MoveIdleBehaviour
        void MoveIdleBehaviour::update(MapObject* object, float dt)
        {
            Base::update(object, dt);
            
            auto gaussianFunc = [](float cycle, float a, float c, float xRange, float& t) -> float
            {
                t = (cycle - (int)cycle);
                if ((((int)cycle) % 2) == 1)
                {
                    t = (1.0f - t);
                }
                
                float x = (xRange * (t-0.5f));
                float result = (a * std::exp(-(x*x) / (2*c*c)));
                
                return result;
            };
            
            auto moveState = object->getOrCreate<MoveIdleStateComponent>();
            
            float movementTime = moveState->getMovementTime();
            float gaussianA = moveState->getGaussianA();
            float gaussianC = moveState->getGaussianC();
            float gaussianXRange = moveState->getGaussianXRange();
            
            float cycle = (moveState->getTime() / movementTime);
            float lastCycle = (moveState->getPreviousTime() / movementTime);
            
            float t = 0.0f;
            float lastT = 0.0f;
            float gaussian = gaussianFunc(cycle, gaussianA, gaussianC, gaussianXRange, t);
            float lastGaussian = gaussianFunc(lastCycle, gaussianA, gaussianC, gaussianXRange, lastT);
            
            float moveY = ((gaussian * moveState->getMovementDistanceY()) - (lastGaussian * moveState->getMovementDistanceY()));
            
            float speedX = (moveState->getMovementDistanceX() / movementTime);
            float moveX = ((t * speedX) - (lastT * speedX));
            
            object->get<PositionComponent>()->movePosition(cocos2d::Vec2(moveX, moveY));
        }
    }
}