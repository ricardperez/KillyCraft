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
		enum GamepadAction
		{
			eNone = 0,
			eMoveLeft = 1,
			eMoveRight = 2,
			eFire = 4
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
			
            struct TouchInfo
            {
                const cocos2d::Touch* touch;
                time_t timestamp;
                
                TouchInfo() : touch(nullptr), timestamp(0) {}
            };
            
			TouchInfo leftTouch;
			TouchInfo rightTouch;
		};
		
		//This class will schedule an update method and call the CommandDirector
		class GamepadController
		{
		public:
			static GamepadController* create();
			virtual ~GamepadController();
			
			Gallant::Signal3<Gamepad*, int /*GamepadAction bitmask*/, float>& getGamepadActionSignal();
			
		private:
			GamepadController();
			
		private:
			Gamepad gamepad;
			cocos2d::Timer* timer;
			
			Gallant::Signal3<Gamepad*, int, float> gamepadActionSignal;
		};
	}
}

#endif /* defined(__KillyCraft__Gamepad__) */
