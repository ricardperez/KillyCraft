//
//  TimeComponent.h
//  KillyCraft
//
//  Created by Ricard Perez del Campo on 31/10/14.
//  Copyright (c) 2014 MelonGames. All rights reserved.
//

#ifndef __KillyCraft__TimeComponent__
#define __KillyCraft__TimeComponent__

#include "Component.h"
#include <map>

namespace MelonGames
{
    namespace KillyCraft
    {
        namespace ComponentsFactory
        {
            Component* createTimeComponent(const Json::Value& json);
        }
        
        class TimeComponent : public Component
        {
        public:
            DECLARE_TYPE_WITH_BASE_TYPE(TimeComponent, Component);
            
            friend Component* ComponentsFactory::createTimeComponent(const Json::Value& json);
            
            TimeComponent();
            
            virtual void update(float dt) override;
            
            float getTime() const;
            
        private:
            float time;
        };
        
        class TimerComponent : public Component
        {
        public:
            DECLARE_TYPE_WITH_BASE_TYPE(TimerComponent, Component);
            
            TimerComponent();
            
            void update(float dt) override;
            bool hasTimer(const std::string& name);
            void addTimer(const std::string& name);
            float getTimer(const std::string& name);
            void resetTimer(const std::string& name);
            
        private:
            std::map<std::string, float> timers;
        };
    }
}

#endif /* defined(__KillyCraft__TimeComponent__) */
