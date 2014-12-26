//
//  GamepadComponent.cpp
//  KillyCraft
//
//  Created by Ricard Perez del Campo on 25/10/14.
//  Copyright (c) 2014 MelonGames. All rights reserved.
//

#include "GamepadComponent.h"
#include "PositionComponent.h"
#include "ViewComponent.h"
#include "WeaponComponent.h"
#include "Gameplay/MapObject.h"
#include "Gameplay/Player.h"
#include "Gameplay/Map.h"
#include "Gameplay/Gamepad.h"
#include "2d/CCSprite.h"

namespace MelonGames
{
    namespace KillyCraft
    {
        GamepadComponent::GamepadComponent()
        : speed(100)
        , minTimeToStartMoving(0.05f)
        , timeLeftToStartMoving(minTimeToStartMoving)
        {
        }
        
        void GamepadComponent::moveObject(float distance) const
        {
            auto posComponent = object->get<PositionComponent>();
            cocos2d::Vec3 positionCp = posComponent->getPosition();
            
            float viewComponentWidth = object->get<ViewComponent>()->getSprite()->getContentSize().width;
            
            float desiredX = positionCp.x + distance;
            float maxX = (object->getMap()->getDefinition().screenSize.width - viewComponentWidth * 0.45f);
            float minX = (viewComponentWidth * 0.45f);
            
            positionCp.x = std::max(minX, std::min(maxX, desiredX));
            
            posComponent->setPosition(positionCp);
        }
        
        void GamepadComponent::update(float dt)
        {
            auto gamepad = object->getMap()->getPlayer()->getGamepad();
            
            bool firing = gamepad->isFiring();
            bool touchingLeft = gamepad->isTouchingLeft();
            bool touchingRight = gamepad->isTouchingRight();
            
            if (firing)
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
            } else if (touchingLeft || touchingRight)
            {
                timeLeftToStartMoving -= dt;
                if (timeLeftToStartMoving <= 0.0f)
                {
                    if (touchingLeft)
                    {
                        moveObject(-speed*dt);
                    }
                    else if (touchingRight)
                    {
                        moveObject(speed*dt);
                    }
                }
            } else
            {
                timeLeftToStartMoving = minTimeToStartMoving;
            }
            
            Base::update(dt);
        }
        
        void GamepadComponent::setSpeed(float speed)
        {
            this->speed = speed;
        }
    }
}