//
//  EvasionBehaviours.h
//  KillyCraft
//
//  Created by Ricard Perez del Campo on 20/01/15.
//  Copyright (c) 2015 MelonGames. All rights reserved.
//

#ifndef __KillyCraft__EvasionBehaviours__
#define __KillyCraft__EvasionBehaviours__

#include "Behaviour.h"

namespace MelonGames
{
    namespace KillyCraft
    {
        class EvadeProjectilesHorizontally : public Behaviour
        {
        public:
            DECLARE_TYPE_WITH_BASE_TYPE(EvadeProjectilesHorizontally, Behaviour);
            
            virtual void update(MapObject* object, float dt) override;
        };
    }
}

#endif /* defined(__KillyCraft__EvasionBehaviours__) */
