//
//  GamepadComponent.cpp
//  KillyCraft
//
//  Created by Ricard Perez del Campo on 25/10/14.
//  Copyright (c) 2014 MelonGames. All rights reserved.
//

#include "GamepadComponent.h"
#include "PositionComponent.h"
#include "WeaponComponent.h"
#include "Gameplay/MapObject.h"
#include "Gameplay/Player.h"
#include "Gameplay/Map.h"
#include "Gameplay/Gamepad.h"

namespace MelonGames
{
    namespace KillyCraft
    {
        GamepadComponent::GamepadComponent()
        : speed(100)
        {
        }
        
        void GamepadComponent::update(float dt)
        {
            auto gamepad = object->getMap()->getPlayer()->getGamepad();
            if (gamepad->isTouchingLeft())
            {
                object->get<PositionComponent>()->movePositionX(-speed*dt);
            }
            else if (gamepad->isTouchingRight())
            {
                object->get<PositionComponent>()->movePositionX(speed*dt);
            }
            
            if (gamepad->isFiring())
            {
                auto weaponComponent = object->get<WeaponComponent>();
                assert(weaponComponent);
                if (weaponComponent)
                {
                    if (weaponComponent->canShoot())
                    {
                        weaponComponent->shoot();
                    }
                }
            }
            
            Base::update(dt);
        }
        
        void GamepadComponent::setSpeed(float speed)
        {
            this->speed = speed;
        }
    }
}