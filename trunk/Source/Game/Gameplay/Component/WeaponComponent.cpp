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
        : nProjectilesLeft(0)
        , fireRate(0.0f)
        , lastShotTime(0.0f)
        {
            
        }
        
        bool WeaponComponent::canShoot() const
        {
            if (nProjectilesLeft > 0)
            {
                float currTime = object->getMap()->getElapsedTime();
                return ((currTime - lastShotTime) >= fireRate);
            }
            
            return false;
        }
        
        void WeaponComponent::shoot()
        {
            lastShotTime = object->getMap()->getElapsedTime();
            
            assert(nProjectilesLeft > 0 && "Should not be shooting as no bullets are left");
            if (nProjectilesLeft > 0)
            {
                --nProjectilesLeft;
            }
            
            if (MapObject* projectile = object->getMap()->getFactory()->createObject(projectileTemplateName))
            {
                projectile->get<PositionComponent>()->setPosition(object->get<PositionComponent>()->getPosition());
                object->getMap()->addObject(projectile);
            }
            
        }
    }
}