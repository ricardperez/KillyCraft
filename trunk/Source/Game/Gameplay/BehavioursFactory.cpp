//
//  BehavioursFactory.cpp
//  KillyCraft
//
//  Created by Ricard Perez del Campo on 06/11/14.
//  Copyright (c) 2014 MelonGames. All rights reserved.
//

#include "Behaviour/Behaviour.h"
#include "Behaviour/MovementBehaviours.h"
#include "Behaviour/DestroyBehaviour.h"
#include "Behaviour/DestroyBehaviourFunctions.h"
#include "json/document.h"

namespace MelonGames
{
    namespace KillyCraft
    {
        namespace BehavioursFactory
        {
            Behaviour* createDestroyBehaviour(const rapidjson::Value& json)
            {
                auto result = new DestroyBehaviour();
                const rapidjson::Value& checks = json["checks"];
                for (auto it = checks.MemberonBegin(); it != checks.MemberonEnd(); ++it)
                {
                    const rapidjson::Value& check = it->value;
                    std::string type = check["type"].GetString();
                    if (type == "OutOfScreen")
                    {
                        result->addCheckFunctionWithName(DestroyBehaviourFunctions::makeIsOutOfScreenFunction(), type);
                    }
                    else if (type == "Collision")
                    {
                        result->addCheckFunctionWithName(DestroyBehaviourFunctions::makeIsCollisionFunction(), type);
                    }
                    else if (type == "Dead")
                    {
                        result->addCheckFunctionWithName(DestroyBehaviourFunctions::makeIsDeadFunction(), type);
                    }
                    else
                    {
                        delete result;
                        return nullptr;
                    }
                }
                
                return result;
            }
            
            Behaviour* createBehaviour(const rapidjson::Value& json)
            {
                std::string type = json["type"].GetString();
                if (type == "Destroy")
                {
                    return createDestroyBehaviour(json);
                }
                else if (type == "MoveCircular")
                {
                    return new MoveCircularBehaviour();
                }
                else if (type == "MoveLinear")
                {
                    return new MoveLinearBehaviour();
                }
                
                return nullptr;
            }
        }
    }
}