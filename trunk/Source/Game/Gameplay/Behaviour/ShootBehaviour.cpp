//
//  ShootBehaviour.cpp
//  KillyCraft
//
//  Created by Ricard Perez del Campo on 05/08/15.
//  Copyright (c) 2015 MelonGames. All rights reserved.
//

#include "ShootBehaviour.h"
#include "Gameplay/Component/WeaponComponent.h"
#include "Gameplay/MapObject.h"

namespace MelonGames
{
    namespace KillyCraft
    {
        void ShootBehaviour::update(MapObject* object, float dt)
        {
            Base::update(object, dt);
            
            if (auto weaponComponent = object->get<WeaponComponent>())
            {
                if (weaponComponent->canShoot())
                {
                    weaponComponent->shoot();
                }
            }
        }
    }
}