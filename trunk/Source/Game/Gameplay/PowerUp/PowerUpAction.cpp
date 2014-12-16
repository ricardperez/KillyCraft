//
//  PowerUpAction.cpp
//  KillyCraft
//
//  Created by Ricard Perez del Campo on 14/12/14.
//  Copyright (c) 2014 MelonGames. All rights reserved.
//

#include "PowerUpAction.h"
#include "Gameplay/MapObject.h"

namespace MelonGames
{
    namespace KillyCraft
    {
        PowerUpAction::PowerUpAction(const PowerUpFunction& f)
        : function(f)
        {
        }
        
        void PowerUpAction::applyToObject(MapObject* object) const
        {
            if (function)
            {
                function(object);
            }
        }
    }
}