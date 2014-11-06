//
//  DestroyBehaviour.h
//  KillyCraft
//
//  Created by Ricard Perez del Campo on 31/10/14.
//  Copyright (c) 2014 MelonGames. All rights reserved.
//

#ifndef __KillyCraft__DestroyBehaviour__
#define __KillyCraft__DestroyBehaviour__

#include "Behaviour.h"
#include <functional>
#include <vector>

namespace MelonGames
{
    namespace KillyCraft
    {
        //Return true means it has to be destroyed
        typedef std::function<bool(MapObject*)> DestroyCheckFunction;
        class DestroyBehaviour : public Behaviour
        {
        public:
            DECLARE_TYPE_WITH_BASE_TYPE(DestroyBehaviour, Behaviour);
            
            virtual void update(MapObject* object, float dt);
            void addCheckFunctionWithName(const DestroyCheckFunction& function, const std::string& name);
            void removeCheckFunctionWithName(const std::string& name);
            
        private:
            struct NamedCheckFunction
            {
                DestroyCheckFunction function;
                std::string name;
            };
            std::vector<NamedCheckFunction> checkFunctions;
        };
    }
}

#endif /* defined(__KillyCraft__DestroyBehaviour__) */
