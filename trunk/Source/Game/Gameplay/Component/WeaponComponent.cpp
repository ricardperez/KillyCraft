//
//  WeaponComponent.cpp
//  KillyCraft
//
//  Created by Ricard Perez del Campo on 25/10/14.
//  Copyright (c) 2014 MelonGames. All rights reserved.
//

#include "WeaponComponent.h"
#include "Gameplay/MapObject.h"
#include "Gameplay/Map.h"
#include "Gameplay/MapObjectsFactory.h"
#include "PositionComponent.h"

namespace MelonGames
{
    namespace KillyCraft
    {
        WeaponComponent::WeaponComponent()
        : nBullets(0)
        , lastShotTime(0.0f)
        {
        }
        
        const Weapon& WeaponComponent::getWeapon() const
        {
            return weapon;
        }
        
        bool WeaponComponent::canShoot() const
        {
            if (nBullets > 0)
            {
                float currTime = object->getMap()->getElapsedTime();
                return ((currTime - lastShotTime) >= weapon.fireRate);
            }
            
            return false;
        }
        
        void WeaponComponent::shoot()
        {
            lastShotTime = object->getMap()->getElapsedTime();
            
            assert(nBullets > 0 && "Should not be shooting as no bullets are left");
            if (nBullets > 0)
            {
                --nBullets;
            }
            
            if (MapObject* projectile = object->getMap()->getFactory()->createObject(weapon.bulletTemplate))
            {
                projectile->get<PositionComponent>()->setPosition(object->get<PositionComponent>()->getPosition());
                object->getMap()->addObject(projectile);
            }
        }
        
        void WeaponComponent::addBullets(unsigned int n)
        {
            nBullets += n;
        }
        
        void WeaponComponent::reset(const Weapon &weapon, int nBullets)
        {
            this->weapon = weapon;
            this->nBullets = nBullets;
            
            if (object)
            {
                assert(object->getMap() && "Map has to exist");
                lastShotTime = object->getMap()->getElapsedTime();
            }
        }
    }
}