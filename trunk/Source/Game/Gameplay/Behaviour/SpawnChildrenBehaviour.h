//
//  SpawnChildrenBehaviour.h
//  KillyCraft
//
//  Created by Ricard Perez del Campo on 28/01/15.
//  Copyright (c) 2015 MelonGames. All rights reserved.
//

#ifndef __KillyCraft__SpawnChildrenBehaviour__
#define __KillyCraft__SpawnChildrenBehaviour__

#include "Behaviour.h"
#include <vector>
#include <string>

namespace MelonGames
{
    namespace KillyCraft
    {
        class SpawnChildrenBehaviour : public Behaviour
        {
        public:
            DECLARE_TYPE_WITH_BASE_TYPE(SpawnChildrenBehaviour, Behaviour);
            
            SpawnChildrenBehaviour(const std::vector<std::string>& childrenTypes);
            virtual void update(MapObject* object, float dt) override;
            
        private:
            const std::vector<std::string> childrenTypes;
        };
    }
}

#endif /* defined(__KillyCraft__SpawnChildrenBehaviour__) */
