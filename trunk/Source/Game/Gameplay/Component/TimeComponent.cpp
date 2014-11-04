//
//  TimeComponent.cpp
//  KillyCraft
//
//  Created by Ricard Perez del Campo on 31/10/14.
//  Copyright (c) 2014 MelonGames. All rights reserved.
//

#include "TimeComponent.h"

namespace MelonGames
{
    namespace KillyCraft
    {
        TimeComponent::TimeComponent()
        : time(0.0f)
        {
        }
        
        void TimeComponent::update(float dt)
        {
            Base::update(dt);
            time += dt;
        }
        
        float TimeComponent::getTime() const
        {
            return time;
        }
    }
}