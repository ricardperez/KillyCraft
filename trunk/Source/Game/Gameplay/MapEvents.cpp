//
//  MapEvents.cpp
//  KillyCraft
//
//  Created by Ricard Perez del Campo on 06/08/15.
//  Copyright (c) 2015 MelonGames. All rights reserved.
//

#include "MapEvents.h"

namespace MelonGames
{
    namespace KillyCraft
    {
        Gallant::Signal1<MapObject*>& MapEvents::getEnemyKilledSignal()
        {
            return enemyKilledSignal;
        }
    }
}