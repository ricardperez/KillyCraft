//
//  Behaviour.h
//  KillyCraft
//
//  Created by Ricard Perez del Campo on 31/10/14.
//  Copyright (c) 2014 MelonGames. All rights reserved.
//

#ifndef __KillyCraft__Behaviour__
#define __KillyCraft__Behaviour__

#include "MelonGames/DeclaredTypes.h"

namespace MelonGames
{
    namespace KillyCraft
    {
        class MapObject;
        
        class Behaviour
        {
        public:
            DECLARE_BASE_TYPE(Behaviour);
            
            virtual void update(MapObject* object, float dt);
        };
    }
}

#endif /* defined(__KillyCraft__Behaviour__) */
