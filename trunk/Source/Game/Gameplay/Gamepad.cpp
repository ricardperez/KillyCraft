//
//  Gamepad.cpp
//  KillyCraft
//
//  Created by Ricard Pérez del Campo on 14/10/14.
//
//

#include "Gamepad.h"
#include "2d/CCNode.h"
#include "base/CCEventListenerTouch.h"
#include "base/CCDirector.h"
#include "base/CCEventDispatcher.h"
#include <chrono>

namespace MelonGames
{
	namespace KillyCraft
	{
#pragma mark - Gamepad
		Gamepad::Gamepad()
		{
			auto eventsListener = cocos2d::EventListenerTouchAllAtOnce::create();
			
			eventsListener->onTouchesBegan = [this](const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event) -> void {
				for (const auto& touch : touches)
				{
					onTouchBegan(touch);
				}
			};
			
			eventsListener->onTouchesEnded = [this](const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event) -> void {
				for (const auto& touch : touches)
				{
					onTouchEnded(touch);
				}
			};
			
			eventsListener->onTouchesCancelled = [this](const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event) -> void {
				for (const auto& touch : touches)
				{
					onTouchEnded(touch);
				}
			};
			
			this->eventsListener = eventsListener;
			
			cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(eventsListener, kEventsListenerPriority);
		}
		
		Gamepad::~Gamepad()
		{
			cocos2d::Director::getInstance()->getEventDispatcher()->removeEventListener(eventsListener);
		}
		
		
		bool Gamepad::isTouchingLeft() const
		{
            if (leftTouch.touch && rightTouch.touch)
            {
                return (leftTouch.timestamp <= rightTouch.timestamp);
            }
			
            return (leftTouch.touch != nullptr);
		}
		
		bool Gamepad::isTouchingRight() const
		{
            if (leftTouch.touch && rightTouch.touch)
            {
                return (leftTouch.timestamp > rightTouch.timestamp);
            }
            
            return (rightTouch.touch != nullptr);
		}
		
		bool Gamepad::isFiring() const
		{
			return ((leftTouch.touch != nullptr) && (rightTouch.touch != nullptr));
		}
		
		void Gamepad::onTouchBegan(const cocos2d::Touch *touch)
		{
			auto position = touch->getLocationInView();
			if (position.x < cocos2d::Director::getInstance()->getWinSize().width * 0.5f)
			{
				if (leftTouch.touch == nullptr)
				{
					leftTouch.touch = touch;
                    leftTouch.timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now().time_since_epoch());
                }
			}
			else
			{
				if (rightTouch.touch == nullptr)
				{
					rightTouch.touch = touch;
                    rightTouch.timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now().time_since_epoch());
				}
			}
		}
		
		void Gamepad::onTouchEnded(const cocos2d::Touch *touch)
		{
			if (touch == leftTouch.touch)
			{
				leftTouch.touch = nullptr;
			}
			if (touch == rightTouch.touch)
			{
				rightTouch.touch = nullptr;
			}
		}
    }
}