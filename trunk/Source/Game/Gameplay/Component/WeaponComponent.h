//
//  WeaponComponent.h
//  KillyCraft
//
//  Created by Ricard Perez del Campo on 25/10/14.
//  Copyright (c) 2014 MelonGames. All rights reserved.
//

#ifndef __KillyCraft__WeaponComponent__
#define __KillyCraft__WeaponComponent__

#include "Component.h"

namespace MelonGames
{
    namespace KillyCraft
    {
        enum class WeaponType
        {
            eNone = 0,
            eMachinegun = 1
        };
        
        class WeaponComponent : public Component
        {
        public:
            DECLARE_TYPE_WITH_BASE_TYPE(WeaponComponent, Component);
            
            WeaponComponent();
            
            void setup(WeaponType weaponType, float shotDelay);
            
            bool canShoot() const;
            void shoot();
            
        private:
            WeaponType weapon;
            
            int nShots;
            float shotDelay;
            float lastShotTime;
        };
    }
}

#endif /* defined(__KillyCraft__WeaponComponent__) */
