//
//  MapTime.cpp
//  KillyCraft
//
//  Created by Ricard Perez del Campo on 15/07/15.
//  Copyright (c) 2015 MelonGames. All rights reserved.
//

#include "MapTime.h"

namespace MelonGames
{
    namespace KillyCraft
    {
        MapTime::MapTime()
        : time(0.0f)
        , lastDt(0.0f)
        {
            
        }
        
        void MapTime::addTime(float dt)
        {
            time += dt;
            lastDt = dt;
        }
        
        float MapTime::getTime() const
        {
            return time;
        }
        
        float MapTime::getLastDt() const
        {
            return lastDt;
        }
    }
}