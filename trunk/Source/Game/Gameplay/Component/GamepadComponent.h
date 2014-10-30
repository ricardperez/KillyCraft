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
        class Gamepad;
        enum class GamepadAction;
        
        class GamepadComponent : public Component
        {
        public:
            DECLARE_TYPE_WITH_BASE_TYPE(GamepadComponent, Component);
            
            virtual void onObjectAttachedToMap() override;
            virtual void onWillDetachFromObject() override;
            
        protected:
            virtual void onGamepadAction(Gamepad* gamepad, GamepadAction action, float dt) = 0;
            
        };
        
        class GamepadMoveComponent : public GamepadComponent
        {
        public:
            DECLARE_TYPE_WITH_BASE_TYPE(GamepadMoveComponent, GamepadComponent);
            
            GamepadMoveComponent();
            
            void setSpeed(float speed);
            void setSpeed(float speedLeft, float speedRight);
            
        protected:
            void onGamepadAction(Gamepad* gamepad, GamepadAction action, float dt);
            
        private:
            float speedLeft;
            float speedRight;
        };
        
        class GamepadShootComponent : public GamepadComponent
        {
        public:
            DECLARE_TYPE_WITH_BASE_TYPE(GamepadShootComponent, GamepadComponent);
            
        protected:
            void onGamepadAction(Gamepad* gamepad, GamepadAction action, float dt);
        };
    }
}

#endif /* defined(__KillyCraft__GamepadComponent__) */
