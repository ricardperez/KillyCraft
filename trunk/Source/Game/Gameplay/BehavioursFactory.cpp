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

#include "json/value.h"
#include "base/ccMacros.h"

namespace MelonGames
{
    namespace KillyCraft
    {
        namespace BehavioursFactory
        {
            Behaviour* createDestroyBehaviour(const Json::Value& json)
            {
                auto result = new DestroyBehaviour();
                for (const auto& check : json["checks"])
                {
                    std::string type = check["type"].asString();
                    if (type == "OutOfScreenDown")
                    {
                        result->addCheckFunctionWithName(DestroyBehaviourFunctions::makeIsOutOfScreenDownFunction(), type);
                    }
                    else if (type == "OutOfScreenUp")
                    {
                        result->addCheckFunctionWithName(DestroyBehaviourFunctions::makeIsOutOfScreenUpFunction(), type);
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
                        CCASSERT(false, ("Could not create a DestroyBehaviour function of type " + type).c_str());
                        delete result;
                        return nullptr;
                    }
                }
                
                return result;
            }
            
            Behaviour* createBehaviour(const Json::Value& json)
            {
                std::string type = json["type"].asString();
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
                else
                {
                    CCASSERT(false, ("Could not create a behaviour of type " + type).c_str());
                }
                
                return nullptr;
            }
        }
    }
}