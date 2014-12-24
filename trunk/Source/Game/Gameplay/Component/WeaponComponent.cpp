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
#include "Gameplay/ObjectsFastFactory.h"

namespace MelonGames
{
    namespace KillyCraft
    {
        WeaponComponent::WeaponComponent()
        : weapon(WeaponType::eNone)
        , nShots(0)
        , shotDelay(0.5f)
        , lastShotTime(0.0f)
        {
            
        }
        
        void WeaponComponent::setup(WeaponType weaponType, float shotDelay)
        {
            this->weapon = weaponType;
            this->shotDelay = shotDelay;
            
            nShots = 0;
        }
        
        bool WeaponComponent::canShoot() const
        {
            if (nShots > 0)
            {
                float currTime = object->getMap()->getElapsedTime();
                return ((currTime - lastShotTime) >= shotDelay);
            }
            
            return true;
        }
        
        void WeaponComponent::shoot()
        {
            lastShotTime = object->getMap()->getElapsedTime();
            ++nShots;
            
            MapObject* projectile = nullptr;
            
            switch (weapon)
            {
                case WeaponType::eMachinegun:
                    projectile = ObjectsFastFactory::getInstance()->createProjectile(object);
                    break;
                default:
                    break;
            }
            
            if (projectile)
            {
                object->getMap()->addObject(projectile);
            }
            
        }
        
        const cocos2d::Vec3& WeaponComponent::getRelativePosition() const
        {
            return relativePosition;
        }
    }
}