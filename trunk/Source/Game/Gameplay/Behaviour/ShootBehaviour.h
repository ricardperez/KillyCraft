//
//  ShootBehaviour.h
//  KillyCraft
//
//  Created by Ricard Perez del Campo on 05/08/15.
//  Copyright (c) 2015 MelonGames. All rights reserved.
//

#ifndef __KillyCraft__ShootBehaviour__
#define __KillyCraft__ShootBehaviour__

#include "Behaviour.h"

namespace MelonGames
{
    namespace KillyCraft
    {
        class ShootBehaviour : public Behaviour
        {
        public:
            DECLARE_TYPE_WITH_BASE_TYPE(ShootBehaviour, Behaviour);
            
            void update(MapObject* object, float dt) override;
        };
    }
}

#endif /* defined(__KillyCraft__ShootBehaviour__) */
