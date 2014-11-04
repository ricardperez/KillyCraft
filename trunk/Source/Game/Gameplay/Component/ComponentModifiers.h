//
//  ComponentModifiers.h
//  KillyCraft
//
//  Created by Ricard Perez del Campo on 31/10/14.
//  Copyright (c) 2014 MelonGames. All rights reserved.
//

#ifndef __KillyCraft__ComponentModifiers__
#define __KillyCraft__ComponentModifiers__

#include "math/Vec3.h"
#include <functional>

namespace MelonGames
{
    namespace KillyCraft
    {
        class MapObject;
        typedef std::function<void(MapObject* object, float dt)> ComponentModifier;
        
        namespace ComponentModifiers
        {
            ComponentModifier makeAccelerateLinearMovement(const cocos2d::Vec3& acceleration, float duration);
            ComponentModifier makeAccelerateCircularMovement(float accelerationInDegrees, float duration);
            ComponentModifier makeChangeRadiusForCircularMovement(float maxRadius, float minRadius, float speed);
        }
    }
}

#endif /* defined(__KillyCraft__ComponentModifiers__) */
