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

namespace MelonGames
{
    namespace KillyCraft
    {
        namespace BehavioursFactory
        {
            Behaviour* createBehaviour(const rapidjson::Value& json);
        }
        
        namespace ComponentsFactoryFunctions
        {
            ComponentFactoryFunction createPositionComponent()
            {
                return [](const rapidjson::Value& json) -> Component*
                {
                    return new PositionComponent();
                };
            }
            
            ComponentFactoryFunction createViewComponent()
            {
                return [](const rapidjson::Value& json) -> Component*
                {
                    auto result = new ViewComponent();
                    result->setSpriteFrameName(json["sprite"].GetString());
                    return result;
                };
            }
            
            ComponentFactoryFunction createBehaviourComponent()
            {
                return [](const rapidjson::Value& json) -> Component*
                {
                    auto result = new BehaviourComponent();
                    const rapidjson::Value& behaviours = json["behaviours"];
                    for (auto it = behaviours.MemberonBegin(); it != behaviours.MemberonEnd(); ++it)
                    {
                        Behaviour* behaviour = BehavioursFactory::createBehaviour(it->value);
                        if (behaviour)
                        {
                            result->addBehaviour(behaviour);
                        }
                        else
                        {
                            delete result;
                            return nullptr;
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
            }
        }
    }
}