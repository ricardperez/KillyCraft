//
//  DestroyBehaviourFunctions.cpp
//  KillyCraft
//
//  Created by Ricard Perez del Campo on 31/10/14.
//  Copyright (c) 2014 MelonGames. All rights reserved.
//

#include "DestroyBehaviourFunctions.h"
#include "DestroyBehaviour.h"
#include "Gameplay/MapObject.h"

namespace MelonGames
{
    namespace KillyCraft
    {
        namespace DestroyBehaviourFunctions
        {
            DestroyCheckFunction makeIsDeadFunction()
            {
                return [](MapObject* object) -> bool
                {
                    return false;
                };
            }
            DestroyCheckFunction makeIsOutOfScreenFunction()
            {
                return [](MapObject* object) -> bool
                {
                    return false;
                };
            }
            
            DestroyCheckFunction makeIsCollisionFunction()
            {
                return [](MapObject* object) -> bool
                {
                    return false;
                };
            }
        }
    }
}