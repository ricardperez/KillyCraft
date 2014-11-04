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
        class LinearMoveStateComponent : public Component
        {
        public:
            DECLARE_TYPE_WITH_BASE_TYPE(LinearMoveStateComponent, Component);
            
            const cocos2d::Vec3& getMovementPerSecond() const;
            void setMovementPerSecond(const cocos2d::Vec3& movementPerSecond);
            
        private:
            cocos2d::Vec3 movementPerSecond;
        };
        
        class CircularMoveStateComponent : public Component
        {
        public:
            DECLARE_TYPE_WITH_BASE_TYPE(CircularMoveStateComponent, Component);
            
            CircularMoveStateComponent();
            
            float getRadiansPerSecond() const;
            void setRadiansPerSecond(float radiansPerSecond);
            float getRadius() const;
            void setRadius(float radius);
            
        private:
            float radiansPerSecond;
            float radius;
        };
    }
}

#endif /* defined(__KillyCraft__MovementStateComponents__) */
