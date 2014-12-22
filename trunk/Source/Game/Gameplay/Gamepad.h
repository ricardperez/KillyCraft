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
#include <chrono>

namespace cocos2d
{
	class EventListener;
	class Touch;
	class Timer;
    class Node;
    
    namespace extension
    {
        class ControlButton;
    }
}

namespace MelonGames
{
	namespace KillyCraft
	{
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
            
            cocos2d::extension::ControlButton* createShootingButton();
			
		private:
			void onTouchBegan(const cocos2d::Touch* touch);
			void onTouchEnded(const cocos2d::Touch* touch);
            
		private:
			cocos2d::EventListener* eventsListener;
			
            struct TouchInfo
            {
                const cocos2d::Touch* touch;
                std::chrono::milliseconds timestamp;
                
                TouchInfo() : touch(nullptr), timestamp(0) {}
            };
            
			TouchInfo leftTouch;
			TouchInfo rightTouch;
            
            bool pressingButton;
		};
	}
}

#endif /* defined(__KillyCraft__Gamepad__) */
