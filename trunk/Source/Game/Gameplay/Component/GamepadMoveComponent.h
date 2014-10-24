//
//  GamepadMoveComponent.h
//  KillyCraft
//
//  Created by Ricard Pérez del Campo on 24/10/14.
//  Copyright (c) 2014 MelonGames. All rights reserved.
//

#ifndef __KillyCraft__GamepadMoveComponent__
#define __KillyCraft__GamepadMoveComponent__

#include "Component.h"

namespace MelonGames
{
	namespace KillyCraft
	{
		class Gamepad;
		enum class GamepadAction;
		
		class GamepadMoveComponent : public Component
		{
		public:
			DECLARE_TYPE_WITH_BASE_TYPE(GamepadMoveComponent, Component);
			
			GamepadMoveComponent();
			
			virtual void onObjectAttachedToMap() override;
			virtual void onWillDetachFromObject() override;
			
			void setSpeed(float speed);
			void setSpeed(float speedLeft, float speedRight);
			
		private:
			void onGamepadAction(Gamepad* gamepad, GamepadAction action, float dt);
			
		private:
			float speedLeft;
			float speedRight;
		};
	}
}

#endif /* defined(__KillyCraft__GamepadMoveComponent__) */
