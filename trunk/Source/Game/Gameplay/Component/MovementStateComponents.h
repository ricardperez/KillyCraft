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
#include "math/Vec3.h"

namespace MelonGames
{
    namespace KillyCraft
    {
        namespace ComponentsFactory
        {
            Component* createMoveLinearStateComponent(const Json::Value& json);
            Component* createMoveCircularStateComponent(const Json::Value& json);
        }
        
        class MoveLinearStateComponent : public Component
        {
        public:
            DECLARE_TYPE_WITH_BASE_TYPE(MoveLinearStateComponent, Component);
            
            friend Component* ComponentsFactory::createMoveLinearStateComponent(const Json::Value& json);
            
            const cocos2d::Vec3& getMovementPerSecond() const;
            void setMovementPerSecond(const cocos2d::Vec3& movementPerSecond);
            
        private:
            cocos2d::Vec3 movementPerSecond;
        };
        
        class MoveCircularStateComponent : public Component
        {
        public:
            DECLARE_TYPE_WITH_BASE_TYPE(MoveCircularStateComponent, Component);
            
            friend class ObjectsFastFactory;
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
    }
}

#endif /* defined(__KillyCraft__MovementStateComponents__) */
