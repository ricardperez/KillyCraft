//
//  BehavioursFactory.cpp
//  KillyCraft
//
//  Created by Ricard Perez del Campo on 06/11/14.
//  Copyright (c) 2014 MelonGames. All rights reserved.
//

#include "BehavioursFactory.h"
#include "Gameplay/Behaviour/MovementBehaviours.h"
#include "Gameplay/Behaviour/DestroyBehaviour.h"
#include "Gameplay/Behaviour/DestroyBehaviourFunctions.h"
#include "Gameplay/Behaviour/EvasionBehaviours.h"

#include "MelonGames/Crypto.h"

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
            
            Behaviour* createMoveVerticallyBehaviour(const Json::Value& json)
            {
                auto result = new MoveLinearBehaviour();
                result->setProjection(MoveLinearBehaviour::Projection::eVertical);
                return result;
            }
            
            Behaviour* createMoveHorizontallyBehaviour(const Json::Value& json)
            {
                auto result = new MoveLinearBehaviour();
                result->setProjection(MoveLinearBehaviour::Projection::eHorizontal);
                return result;
            }
            
            template <class T>
            Behaviour* createDefaultBehaviour(const Json::Value& json)
            {
                return new T();
            }
            
            Behaviour* createBehaviour(const Json::Value& json)
            {
                static std::map<unsigned int, std::function<Behaviour*(const Json::Value&)>> lambdas = {
                    {Crypto::stringHash("Destroy"), createDestroyBehaviour},
                    {Crypto::stringHash("MoveLinear"), createDefaultBehaviour<MoveLinearBehaviour>},
                    {Crypto::stringHash("MoveVertically"), createMoveVerticallyBehaviour},
                    {Crypto::stringHash("MoveHorizontally"), createMoveHorizontallyBehaviour},
                    {Crypto::stringHash("MoveCircular"), createDefaultBehaviour<MoveCircularBehaviour>},
                    {Crypto::stringHash("MoveCircularProjected"), createDefaultBehaviour<MoveCircularProjectedBehaviour>},
                    {Crypto::stringHash("EvadeProjectilesHorizontally"), createDefaultBehaviour<EvadeProjectilesHorizontally>},
                };
                
                std::string type = json["type"].asString();
                unsigned int key = Crypto::stringHash(type);
                
                auto lambdaIt = lambdas.find(key);
                if (lambdaIt != lambdas.end())
                {
                    return lambdaIt->second(json);
                }
                
                CCASSERT(false, ("Could not create a behaviour of type " + type).c_str());
                
                return nullptr;
            }
        }
    }
}