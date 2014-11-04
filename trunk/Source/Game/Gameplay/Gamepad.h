//
//  Gamepad.h
//  KillyCraft
//
//  Created by Ricard Pérez del Campo on 14/10/14.
//
//

#ifndef __KillyCraft__Gamepad__
#define __KillyCraft__Gamepad__

#include <set>
#include "libs/Signal/Signal.h"

namespace cocos2d
{
	class EventListener;
	class Touch;
	class Timer;
}

namespace MelonGames
{
	namespace KillyCraft
	{
		enum class GamepadAction
		{
			eNone = 0,
			eMoveLeft,
			eMoveRight,
			eFire
		};
		
		class Gamepad
		{
		public:
			static const int kEventsListenerPriority = 10;
		public:
			Gamepad();
			virtual ~Gamepad();
			
			bool isTouchingLeft() const;
			bool isTouchingRight() const;
			bool isFiring() const;
			
		private:
			void onTouchBegan(const cocos2d::Touch* touch);
			void onTouchEnded(const cocos2d::Touch* touch);
			
		private:
			cocos2d::EventListener* eventsListener;
			
			const cocos2d::Touch* leftTouch;
			const cocos2d::Touch* rightTouch;
		};
		
		//This class will schedule an update method and call the CommandDirector
		class GamepadController
		{
		public:
			static GamepadController* create();
			virtual ~GamepadController();
			
			Gallant::Signal3<Gamepad*, GamepadAction, float>& getGamepadActionSignal();
			
		private:
			GamepadController();
			
		private:
			Gamepad gamepad;
			cocos2d::Timer* timer;
			
			Gallant::Signal3<Gamepad*, GamepadAction, float> gamepadActionSignal;
		};
	}
}

#endif /* defined(__KillyCraft__Gamepad__) */
