//
//  ComponentsFactoryFunctions.cpp
//  KillyCraft
//
//  Created by Ricard Perez del Campo on 06/11/14.
//  Copyright (c) 2014 MelonGames. All rights reserved.
//

#include "MapObjectsFactory.h"
#include "Component/Component.h"
#include "Component/PositionComponent.h"
#include "Component/ViewComponent.h"
#include "Component/WeaponComponent.h"
#include "Component/BehaviourComponent.h"
#include "Component/MovementStateComponents.h"
#include "Component/CollisionDetectionComponent.h"

#include "base/ccMacros.h"

namespace MelonGames
{
    namespace KillyCraft
    {
        namespace BehavioursFactory
        {
            Behaviour* createBehaviour(const Json::Value& json);
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
                    auto result = new CircularMoveStateComponent();
                    result->setRadiansPerSecond(json["rps"].asFloat());
                    result->setRadius(json["r"].asFloat());
                    return result;
                };
            }
            
            ComponentFactoryFunction createMoveLinearComponent()
            {
                return [](const Json::Value& json) -> Component*
                {
                    auto result = new LinearMoveStateComponent();
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
            
            void registerFunctions(std::map<std::string, ComponentFactoryFunction>& functions)
            {
                functions["Position"] = createPositionComponent();
                functions["View"] = createViewComponent();
                functions["Behaviour"] = createBehaviourComponent();
                functions["MoveCircular"] = createMoveCircularComponent();
                functions["MoveLinear"] = createMoveLinearComponent();
                functions["CollisionDetection"] = createCollisionDetectionComponent();
            }
        }
    }
}