//
//  DestroyBehaviourFunctions.h
//  KillyCraft
//
//  Created by Ricard Perez del Campo on 06/11/14.
//  Copyright (c) 2014 MelonGames. All rights reserved.
//

#ifndef KillyCraft_DestroyBehaviourFunctions_h
#define KillyCraft_DestroyBehaviourFunctions_h

#include "DestroyBehaviour.h"

namespace MelonGames
{
    namespace KillyCraft
    {
        class MapObject;
        
        namespace DestroyBehaviourFunctions
        {
            bool isDead(MapObject* object);
            bool isOutOfScreenDown(MapObject* object);
            bool isOutOfScreenUp(MapObject* object);
            bool isCollision(MapObject* object);
        }
    }
}

#endif
