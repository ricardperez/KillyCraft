//
//  PowerUp.h
//  KillyCraft
//
//  Created by Ricard Perez del Campo on 14/12/14.
//  Copyright (c) 2014 MelonGames. All rights reserved.
//

#ifndef __KillyCraft__PowerUp__
#define __KillyCraft__PowerUp__

#include <functional>

namespace MelonGames
{
    namespace KillyCraft
    {
        class MapObject;
        
        typedef std::function<void(MapObject*)> PowerUpFunction;
        
        class PowerUp
        {
        public:
            PowerUp();
            virtual ~PowerUp();
            
            void setFunction(const PowerUpFunction& f);
            
            void applyToObject(MapObject* object) const;
            
        private:
            PowerUpFunction function;
        };
    }
}

#endif /* defined(__KillyCraft__PowerUp__) */
