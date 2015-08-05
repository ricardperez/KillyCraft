//
//  MovementStateComponents.h
//  KillyCraft
//
//  Created by Ricard Perez del Campo on 31/10/14.
//  Copyright (c) 2014 MelonGames. All rights reserved.
//

#ifndef __KillyCraft__MovementStateComponents__
#define __KillyCraft__MovementStateComponents__

#include "Component.h"
#include "math/Vec2.h"

namespace MelonGames
{
    namespace KillyCraft
    {
        namespace ComponentsFactory
        {
            Component* createMoveLinearStateComponent(const Json::Value& json);
            Component* createMoveCircularStateComponent(const Json::Value& json);
            Component* createMoveIdleStateComponent(const Json::Value& json);
        }
        
        class MoveLinearStateComponent : public Component
        {
        public:
            DECLARE_TYPE_WITH_BASE_TYPE(MoveLinearStateComponent, Component);
            
            friend Component* ComponentsFactory::createMoveLinearStateComponent(const Json::Value& json);
            
            MoveLinearStateComponent();
            
            const cocos2d::Vec2& getMovementPerSecond() const;
            void setMovementPerSecond(const cocos2d::Vec2& movementPerSecond);
            
            float getBackgroundSpeedMultiplier() const;
            void setBackgroundSpeedMultiplier(float backgroundSpeedMultiplier);
            
        private:
            cocos2d::Vec2 movementPerSecond;
            float backgroundSpeedMultiplier;
        };
        
        class MoveCircularStateComponent : public Component
        {
        public:
            DECLARE_TYPE_WITH_BASE_TYPE(MoveCircularStateComponent, Component);
            
            friend Component* ComponentsFactory::createMoveCircularStateComponent(const Json::Value& json);
            
            MoveCircularStateComponent();
            
            float getRadiansPerSecond() const;
            float getPeriod() const;
            void setRadiansPerSecond(float radsPerSec);
            void setPeriod(float period);
            float getRadius() const;
            void setRadius(float rad);
            
        private:
            float radiansPerSecond;
            float radius;
        };
        
        class MoveIdleStateComponent : public Component
        {
        public:
            DECLARE_TYPE_WITH_BASE_TYPE(MoveIdleStateComponent, Component);
            
            friend Component* ComponentsFactory::createMoveIdleStateComponent(const Json::Value& json);
            
            MoveIdleStateComponent();
            
            void update(float dt) override;
            
            float getMovementDistanceX() const;
            float getMovementDistanceY() const;
            float getMovementTime() const;
            float getGaussianA() const;
            float getGaussianC() const;
            float getGaussianXRange() const;
            
            float getTime() const;
            float getPreviousTime() const;
            
        private:
            float movementDistanceX;
            float movementDistanceY;
            float movementTime;
            float gaussianA;
            float gaussianC;
            float gaussianXRange;
            
            float time;
            float prevTime;
            float idleTime;
        };
    }
}

#endif /* defined(__KillyCraft__MovementStateComponents__) */
