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
#include "Gameplay/Behaviour/SpawnChildrenBehaviour.h"

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
                static std::map<unsigned int, DestroyCheckFunction> lambdas = {
                    {Crypto::stringHash("OutOfScreenDown"), DestroyBehaviourFunctions::isOutOfScreenDown},
                    {Crypto::stringHash("OutOfScreenUp"), DestroyBehaviourFunctions::isOutOfScreenUp},
                    {Crypto::stringHash("Collision"), DestroyBehaviourFunctions::isCollision},
                    {Crypto::stringHash("Dead"), DestroyBehaviourFunctions::isDead},
                    {Crypto::stringHash("Void"), [](MapObject*)->bool { return true; }},
                };
                
                auto result = new DestroyBehaviour();
                for (const auto& check : json["checks"])
                {
                    std::string type = check["type"].asString();
                    auto it = lambdas.find(Crypto::stringHash(type));
                    if (it != lambdas.end())
                    {
                        result->addCheckFunctionWithName(it->second, type);
                    }
                    else
                    {
                        CCASSERT(false, ("Could not create a DestroyBehaviour function of type " + type).c_str());
                        delete result;
                        return nullptr;
                    }
                }
                
                result->fadeOutTime = json["fadeOut"].asFloat();
                
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
            
            Behaviour* createSpawnChildrenBehaviour(const Json::Value& json)
            {
                std::vector<std::string> childrenTypes;
                for (const auto& childJson : json["children"])
                {
                    childrenTypes.push_back(childJson.asString());
                }
                
                auto result = new SpawnChildrenBehaviour(childrenTypes);
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
                    {Crypto::stringHash("MoveWithBackground"), createDefaultBehaviour<MoveWithBackgroundBehaviour>},
                    {Crypto::stringHash("MoveLinear"), createDefaultBehaviour<MoveLinearBehaviour>},
                    {Crypto::stringHash("MoveVertically"), createMoveVerticallyBehaviour},
                    {Crypto::stringHash("MoveHorizontally"), createMoveHorizontallyBehaviour},
                    {Crypto::stringHash("MoveCircular"), createDefaultBehaviour<MoveCircularBehaviour>},
                    {Crypto::stringHash("MoveCircularProjected"), createDefaultBehaviour<MoveCircularProjectedBehaviour>},
                    {Crypto::stringHash("MoveIdle"), createDefaultBehaviour<MoveIdleBehaviour>},
                    {Crypto::stringHash("EvadeProjectilesHorizontally"), createDefaultBehaviour<EvadeProjectilesHorizontally>},
                    {Crypto::stringHash("SpawnChildren"), createSpawnChildrenBehaviour},
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