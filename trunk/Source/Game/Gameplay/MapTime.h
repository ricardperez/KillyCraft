//
//  MapTime.h
//  KillyCraft
//
//  Created by Ricard Perez del Campo on 15/07/15.
//  Copyright (c) 2015 MelonGames. All rights reserved.
//

#ifndef __KillyCraft__MapTime__
#define __KillyCraft__MapTime__

namespace MelonGames
{
    namespace KillyCraft
    {
        class MapTime
        {
        public:
            MapTime();
            
            void addTime(float dt);
            float getTotalTime() const;
            float getStageTime() const;
            float getLastDt() const;
            
            void clearStage();
            
        private:
            float totalTime;
            float stageTime;
            float lastDt;
        };
    }
}

#endif /* defined(__KillyCraft__MapTime__) */
