//
//  DestroyBehaviour.cpp
//  KillyCraft
//
//  Created by Ricard Perez del Campo on 31/10/14.
//  Copyright (c) 2014 MelonGames. All rights reserved.
//

#include "DestroyBehaviour.h"
#include "Gameplay/MapObject.h"
#include "Gameplay/Map.h"
#include "Gameplay/Component/ViewComponent.h"
#include "Gameplay/Component/TimeComponent.h"
#include "Gameplay/Component/CollisionDetectionComponent.h"

namespace MelonGames
{
    namespace KillyCraft
    {
        DestroyBehaviour::DestroyBehaviour()
        : fadeOutTime(0.0f)
        {
            
        }
        
        void DestroyBehaviour::update(MapObject* object, float dt)
        {
            Base::update(object, dt);
            
            const std::string fadeTimerName = "DestroyBehaviour-FadeOut";
            auto timerComponent = object->getOrCreate<TimerComponent>();
            if (timerComponent->hasTimer(fadeTimerName))
            {
                if (timerComponent->getTimer(fadeTimerName) >= fadeOutTime)
                {
                    object->getMap()->removeObjectWhenPossible(object);
                }
            }
            else
            {
                for (const auto& namedFunction : checkFunctions)
                {
                    if (namedFunction.function(object))
                    {
                        if (auto viewComponent = object->get<ViewComponent>())
                        {
                            viewComponent->setVisible(false);
                        }
                        if (auto collisionDetectionComponent = object->get<CollisionDetectionComponent>())
                        {
                            collisionDetectionComponent->invalidate();
                        }
                        if (fadeOutTime <= 0.0f)
                        {
                            object->getMap()->removeObjectWhenPossible(object);
                        }
                        else
                        {
                            timerComponent->addTimer(fadeTimerName);
                        }
                        break;
                    }
                }
            }
        }
        
        void DestroyBehaviour::addCheckFunctionWithName(const DestroyCheckFunction &function, const std::string &name)
        {
            NamedCheckFunction namedFunction;
            namedFunction.function = function;
            namedFunction.name = name;
            checkFunctions.push_back(namedFunction);
        }
        
        void DestroyBehaviour::removeCheckFunctionWithName(const std::string &name)
        {
            for (auto it = checkFunctions.begin(); it != checkFunctions.end(); ++it)
            {
                if (it->name == name)
                {
                    checkFunctions.erase(it);
                    break;
                }
            }
        }
    }
}