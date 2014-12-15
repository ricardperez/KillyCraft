//
//  PowerUp.cpp
//  KillyCraft
//
//  Created by Ricard Perez del Campo on 14/12/14.
//  Copyright (c) 2014 MelonGames. All rights reserved.
//

#include "PowerUp.h"
#include "Gameplay/MapObject.h"

namespace MelonGames
{
    namespace KillyCraft
    {
        PowerUp::PowerUp()
        : function(nullptr)
        {
        }
        
        PowerUp::~PowerUp()
        {
        }
        
        void PowerUp::setFunction(const PowerUpFunction& f)
        {
            function = f;
        }
        
        void PowerUp::applyToObject(MapObject* object) const
        {
            if (function)
            {
                function(object);
            }
        }
    }
}