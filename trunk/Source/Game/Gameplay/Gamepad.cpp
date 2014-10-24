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
#include "base/CCScheduler.h"

namespace MelonGames
{
	namespace KillyCraft
	{
		Gamepad::Gamepad()
		: leftTouch(nullptr)
		, rightTouch(nullptr)
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
			return ((leftTouch != nullptr) && (rightTouch == nullptr));
		}
		
		bool Gamepad::isTouchingRight() const
		{
			return ((rightTouch != nullptr) && (leftTouch == nullptr));
		}
		
		bool Gamepad::isFiring() const
		{
			return ((leftTouch != nullptr) && (rightTouch != nullptr));
		}
		
		void Gamepad::onTouchBegan(const cocos2d::Touch *touch)
		{
			auto position = touch->getLocationInView();
			if (position.x < cocos2d::Director::getInstance()->getWinSize().width * 0.5f)
			{
				if (leftTouch == nullptr)
				{
					leftTouch = touch;
				}
			}
			else
			{
				if (rightTouch == nullptr)
				{
					rightTouch = touch;
				}
			}
		}
		
		void Gamepad::onTouchEnded(const cocos2d::Touch *touch)
		{
			if (touch == leftTouch)
			{
				leftTouch = nullptr;
			}
			if (touch == rightTouch)
			{
				rightTouch = nullptr;
			}
		}
		
		
		
		GamepadController* GamepadController::create()
		{
			return new GamepadController();
		}
		
		GamepadController::GamepadController()
		: timer(nullptr)
		{
			auto update = [this](float dt){
				GamepadAction action = GamepadAction::eNone;
				
				bool touching = true;
				
				if (gamepad.isTouchingLeft())
				{
					action = GamepadAction::eMoveLeft;
				}
				else if (gamepad.isTouchingRight())
				{
					action = GamepadAction::eMoveRight;
				}
				else if (gamepad.isFiring())
				{
					action = GamepadAction::eFire;
				}
				else
				{
					touching = false;
				}
				
				if (touching)
				{
					gamepadActionSignal.Emit(&gamepad, action, dt);
				}
			};
			
			auto scheduler = cocos2d::Director::getInstance()->getScheduler();
			auto timer = new cocos2d::TimerTargetCallback();
			if (timer->initWithCallback(scheduler, update, nullptr, "", 0.0f, true, 0.0f))
			{
				scheduler->scheduleUpdate(timer, 0, false);
				this->timer = timer;
			}
			else
			{
				delete timer;
			}
		}
		
		GamepadController::~GamepadController()
		{
			delete timer;
		}
		
		Gallant::Signal3<Gamepad*, GamepadAction, float>& GamepadController::getGamepadActionSignal()
		{
			return gamepadActionSignal;
		}
		
	}
}