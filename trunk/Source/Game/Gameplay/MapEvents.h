//
//  MapEvents.h
//  KillyCraft
//
//  Created by Ricard Perez del Campo on 06/08/15.
//  Copyright (c) 2015 MelonGames. All rights reserved.
//

#ifndef __KillyCraft__MapEvents__
#define __KillyCraft__MapEvents__

#include "Signal/Signal.h"

namespace MelonGames
{
    namespace KillyCraft
    {
        class MapObject;
        
        class MapEvents
        {
        public:
            Gallant::Signal1<MapObject*>& getEnemyKilledSignal();
            
        private:
            Gallant::Signal1<MapObject*> enemyKilledSignal;
        };
    }
}

#endif /* defined(__KillyCraft__MapEvents__) */
