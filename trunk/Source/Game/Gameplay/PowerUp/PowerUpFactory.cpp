//
//  PowerUpFactory.cpp
//  KillyCraft
//
//  Created by Ricard Perez del Campo on 14/12/14.
//  Copyright (c) 2014 MelonGames. All rights reserved.
//

#include "PowerUpFactory.h"
#include "PowerUpAction.h"
#include "Gameplay/MapObjectInspector.h"
#include "Gameplay/MapObject.h"
#include "Gameplay/Map.h"
#include "Gameplay/Player.h"
#include "Crypto.h"

namespace MelonGames
{
    namespace KillyCraft
    {
        namespace PowerUpFactory
        {
            PowerUpFunction createHealFunction(const Json::Value& json)
            {
                return [json](MapObject* object)->void
                {
                    if (MapObjectInspector::isPlayer(object))
                    {
                        unsigned int nLives = json["amount"].asUInt();
                        object->getMap()->getPlayer()->addLives(nLives);
                    }
                };
            }
            
            const PowerUpAction* createPowerUpAction(const Json::Value& json)
            {
                static std::map<unsigned int, std::function<PowerUpFunction(const Json::Value&)>> lambdas = {
                    {Crypto::stringHash("Heal"), createHealFunction},
                };
                
                std::string action = json["type"].asString();
                unsigned int actionHash = Crypto::stringHash(action);
                
                auto lambdaIt = lambdas.find(actionHash);
                if (lambdaIt != lambdas.end())
                {
                    return (new PowerUpAction(lambdaIt->second(json)));
                }
                
                return nullptr;
            }
        }
    }
}