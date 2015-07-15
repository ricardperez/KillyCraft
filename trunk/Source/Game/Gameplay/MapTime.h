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
            float getTime() const;
            float getLastDt() const;
            
        private:
            float time;
            float lastDt;
        };
    }
}

#endif /* defined(__KillyCraft__MapTime__) */
