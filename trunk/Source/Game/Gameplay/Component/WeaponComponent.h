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
#include "math/Vec3.h"

namespace MelonGames
{
    namespace KillyCraft
    {
        namespace ComponentsFactory
        {
            Component* createWeaponComponent(const Json::Value& json);
        }
        
        class WeaponComponent : public Component
        {
        public:
            DECLARE_TYPE_WITH_BASE_TYPE(WeaponComponent, Component);
            
            friend Component* ComponentsFactory::createWeaponComponent(const Json::Value& json);
            
            WeaponComponent();
            
            bool canShoot() const;
            void shoot();
            
        private:
            unsigned int nProjectilesLeft;
            float fireRate;
            std::string projectileTemplateName;
            
            float lastShotTime;
        };
    }
}

#endif /* defined(__KillyCraft__WeaponComponent__) */
