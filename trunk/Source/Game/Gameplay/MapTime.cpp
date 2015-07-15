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
        : totalTime(0.0f)
        , stageTime(0.0f)
        , lastDt(0.0f)
        {
            
        }
        
        void MapTime::addTime(float dt)
        {
            totalTime += dt;
            stageTime += dt;
            lastDt = dt;
        }
        
        float MapTime::getTotalTime() const
        {
            return totalTime;
        }
        
        float MapTime::getStageTime() const
        {
            return stageTime;
        }
        
        float MapTime::getLastDt() const
        {
            return lastDt;
        }
        
        void MapTime::clearStage()
        {
            stageTime = 0.0f;
        }
    }
}