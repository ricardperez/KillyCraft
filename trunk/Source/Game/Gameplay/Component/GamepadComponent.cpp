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
        void GamepadComponent::onObjectAttachedToMap()
        {
            Base::onObjectAttachedToMap();
            
            object->getMap()->getPlayer()->getGamepadController()->getGamepadActionSignal().Connect(this, &GamepadComponent::onGamepadAction);
        }
        
        void GamepadComponent::onWillDetachFromObject()
        {
            object->getMap()->getPlayer()->getGamepadController()->getGamepadActionSignal().Disconnect(this, &GamepadComponent::onGamepadAction);
            
            Base::onWillDetachFromObject();
        }
        
        GamepadMoveComponent::GamepadMoveComponent()
        : speedLeft(100)
        , speedRight(100)
        {
            
        }
        
        void GamepadMoveComponent::setSpeed(float speed)
        {
            speedLeft = speed;
            speedRight = speed;
        }
        
        void GamepadMoveComponent::setSpeed(float speedLeft, float speedRight)
        {
            this->speedLeft = speedLeft;
            this->speedRight = speedRight;
        }
        
        void GamepadMoveComponent::onGamepadAction(Gamepad* gamepad, int action, float dt)
        {
            PositionComponent* posComponent = object->get<PositionComponent>();
            cocos2d::Vec3 position = posComponent->getPosition();
            
            float movement = 0.0f;
            
            if (action & GamepadAction::eMoveLeft)
            {
                movement = -speedLeft * dt;
            }
            else if (action & GamepadAction::eMoveRight)
            {
                movement = speedRight * dt;
            }
            
            position.x += movement;
            
            //clamp it
            
            posComponent->setPosition(position);
        }
        
        void GamepadShootComponent::onGamepadAction(Gamepad* gamepad, int action, float dt)
        {
            if (action & GamepadAction::eFire)
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
        }
    }
}