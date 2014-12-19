//
//  ComponentsFactoryFunctions.cpp
//  KillyCraft
//
//  Created by Ricard Perez del Campo on 06/11/14.
//  Copyright (c) 2014 MelonGames. All rights reserved.
//

#include "Gameplay/MapObjectsFactory.h"
#include "Gameplay/Component/Component.h"
#include "Gameplay/Component/PositionComponent.h"
#include "Gameplay/Component/ViewComponent.h"
#include "Gameplay/Component/WeaponComponent.h"
#include "Gameplay/Component/BehaviourComponent.h"
#include "Gameplay/Component/MovementStateComponents.h"
#include "Gameplay/Component/CollisionDetectionComponent.h"
#include "Gameplay/Component/PowerUpComponent.h"

#include "base/ccMacros.h"
#include "base/ccTypes.h"

namespace MelonGames
{
    namespace KillyCraft
    {
        namespace BehavioursFactory
        {
            Behaviour* createBehaviour(const Json::Value& json);
        }
        
        namespace PowerUpFactory
        {
            const PowerUpAction* createPowerUpAction(const Json::Value& json);
        }
        
        namespace ComponentsFactoryFunctions
        {
            cocos2d::Vec3 vec3FromJson(const Json::Value& json)
            {
                cocos2d::Vec3 result(json[0].asFloat(), json[1].asFloat(), json[2].asFloat());
                return result;
            }
            
            ComponentFactoryFunction createPositionComponent()
            {
                return [](const Json::Value& json) -> Component*
                {
                    return new PositionComponent();
                };
            }
            
            ComponentFactoryFunction createViewComponent()
            {
                return [](const Json::Value& json) -> Component*
                {
                    auto result = new ViewComponent();
                    
                    result->setSpriteFrameName(json["sprite"].asString());
                    
                    const Json::Value& tintValue = json["tint"];
                    if (!tintValue.isNull())
                    {
                        result->setTintColor(cocos2d::Color3B(tintValue[0].asInt(), tintValue[1].asInt(), tintValue[2].asInt()));
                    }
                    
                    return result;
                };
            }
            
            ComponentFactoryFunction createBehaviourComponent()
            {
                return [](const Json::Value& json) -> Component*
                {
                    auto result = new BehaviourComponent();
                    for (const auto& behaviourJson : json["behaviours"])
                    {
                        Behaviour* behaviour = BehavioursFactory::createBehaviour(behaviourJson);
                        CCASSERT(behaviour, "Failed creating a behaviour");
                        
                        if (behaviour)
                        {
                            result->addBehaviour(behaviour);
                        }
                    }
                    return result;
                };
            }
            
            ComponentFactoryFunction createMoveCircularComponent()
            {
                return [](const Json::Value& json) -> Component*
                {
                    auto result = new MoveCircularStateComponent();
                    
                    const Json::Value& radsPerSec = json["radsPerSec"];
                    const Json::Value& period = json["period"];
                    if (!radsPerSec.isNull())
                    {
                        result->setRadiansPerSecond(radsPerSec.asFloat());
                    }
                    else if (!period.isNull())
                    {
                        result->setPeriod(period.asFloat());
                    }
                    else
                    {
                        CCASSERT(false, "One of radsPerSec or period has to be defined");
                    }
                    
                    result->setRadius(json["raius"].asFloat());
                    return result;
                };
            }
            
            ComponentFactoryFunction createMoveLinearComponent()
            {
                return [](const Json::Value& json) -> Component*
                {
                    auto result = new MoveLinearStateComponent();
                    result->setMovementPerSecond(vec3FromJson(json["move"]));
                    return result;
                };
            }
            
            ComponentFactoryFunction createCollisionDetectionComponent()
            {
                return [](const Json::Value& json) -> Component*
                {
                    auto result = new CollisionDetectionComponent();
                    result->setCollisionMaskFileName(json["mask"].asString());
                    result->setType((CollisionDetectionType)json["t"].asInt());
                    return result;
                };
            }
            
            ComponentFactoryFunction createPowerUpComponent()
            {
                return [](const Json::Value& json) -> Component*
                {
                    auto result = new PowerUpComponent();
                    for (const auto& action : json["actions"])
                    {
                        if (const auto powerUpAction = PowerUpFactory::createPowerUpAction(action))
                        {
                            result->addPowerUpAction(powerUpAction);
                        }
                    }
                    return result;
                };
            }
            
            void registerFunctions(std::map<std::string, ComponentFactoryFunction>& functions)
            {
                functions["Position"] = createPositionComponent();
                functions["View"] = createViewComponent();
                functions["Behaviour"] = createBehaviourComponent();
                functions["MoveCircular"] = createMoveCircularComponent();
                functions["MoveLinear"] = createMoveLinearComponent();
                functions["CollisionDetection"] = createCollisionDetectionComponent();
                functions["PowerUp"] = createPowerUpComponent();
            }
        }
    }
}