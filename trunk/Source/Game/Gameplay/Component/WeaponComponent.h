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
        
        struct Weapon
        {
            std::string bulletTemplate;
            float fireRate;
            
            Weapon(const std::string& bulletTemplate, float fireRate) : bulletTemplate(bulletTemplate), fireRate(fireRate) {}
            Weapon() : fireRate(0.0f) {}
            
            bool operator==(const Weapon& other) const { return bulletTemplate == other.bulletTemplate; }
        };
        
        class WeaponComponent : public Component
        {
        public:
            DECLARE_TYPE_WITH_BASE_TYPE(WeaponComponent, Component);
            
            friend Component* ComponentsFactory::createWeaponComponent(const Json::Value& json);
            
            WeaponComponent();
            
            const Weapon& getWeapon() const;
            
            bool canShoot() const;
            void shoot();
            
            void addBullets(unsigned int n);
            void reset(const Weapon& weapon, int nBullets);
            
        private:
            Weapon weapon;
            unsigned int nBullets;
            
            float lastShotTime;
        };
    }
}

#endif /* defined(__KillyCraft__WeaponComponent__) */
