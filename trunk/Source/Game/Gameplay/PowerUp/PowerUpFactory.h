//
//  PowerUpFactory.h
//  KillyCraft
//
//  Created by Ricard Perez del Campo on 14/12/14.
//  Copyright (c) 2014 MelonGames. All rights reserved.
//

#ifndef __KillyCraft__PowerUpFactory__
#define __KillyCraft__PowerUpFactory__

#include "json/json.h"

namespace MelonGames
{
    namespace KillyCraft
    {
        class PowerUp;
        
        namespace PowerUpFactory
        {
            PowerUp* createPowerUp(const Json::Value& json);
        }
    }
}

#endif /* defined(__KillyCraft__PowerUpFactory__) */
