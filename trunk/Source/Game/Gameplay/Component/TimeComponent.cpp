//
//  TimeComponent.cpp
//  KillyCraft
//
//  Created by Ricard Perez del Campo on 31/10/14.
//  Copyright (c) 2014 MelonGames. All rights reserved.
//

#include "TimeComponent.h"

namespace MelonGames
{
    namespace KillyCraft
    {
#pragma mark - TimeComponent
        TimeComponent::TimeComponent()
        : time(0.0f)
        {
        }
        
        void TimeComponent::update(float dt)
        {
            Base::update(dt);
            time += dt;
        }
        
        float TimeComponent::getTime() const
        {
            return time;
        }
        
#pragma mark - TimerComponent
        TimerComponent::TimerComponent()
        {
            
        }
        
        void TimerComponent::update(float dt)
        {
            Base::update(dt);
            
            for (auto& pair : timers)
            {
                pair.second += dt;
            }
        }
        
        bool TimerComponent::hasTimer(const std::string& name)
        {
            return (timers.find(name) != timers.end());
        }
        
        void TimerComponent::addTimer(const std::string& name)
        {
            timers[name] = 0.0f;
        }
        
        float TimerComponent::getTimer(const std::string& name)
        {
            auto it = timers.find(name);
            if (it != timers.end())
            {
                return it->second;
            }
            
            return 0.0f;
        }
        
        void TimerComponent::resetTimer(const std::string& name)
        {
            auto it = timers.find(name);
            if (it != timers.end())
            {
                it->second = 0.0f;
            }
        }
    }
}