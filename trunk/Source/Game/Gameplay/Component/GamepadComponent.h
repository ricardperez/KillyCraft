//
//  GamepadComponent.h
//  KillyCraft
//
//  Created by Ricard Perez del Campo on 25/10/14.
//  Copyright (c) 2014 MelonGames. All rights reserved.
//

#ifndef __KillyCraft__GamepadComponent__
#define __KillyCraft__GamepadComponent__

#include "Component.h"

namespace MelonGames
{
    namespace KillyCraft
    {
        namespace ComponentsFactory
        {
            Component* createGamepadComponent(const Json::Value& json);
        }
        
        class Gamepad;
        
        class GamepadComponent : public Component
        {
        public:
            DECLARE_TYPE_WITH_BASE_TYPE(GamepadComponent, Component);
            
            friend Component* ComponentsFactory::createGamepadComponent(const Json::Value& json);
            
            GamepadComponent();
            
            virtual void update(float dt) override;
            
            void setSpeed(float speed);
            
        private:
            void moveObject(float distance) const;
            
        private:
            float speed;
            const float minTimeToStartMoving;
            float timeLeftToStartMoving;
        };
    }
}

#endif /* defined(__KillyCraft__GamepadComponent__) */
