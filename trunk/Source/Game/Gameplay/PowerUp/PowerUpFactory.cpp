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
#include "Gameplay/Component/WeaponComponent.h"
#include "MelonGames/Crypto.h"

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
            
            PowerUpFunction createWeaponFunction(const Json::Value& json)
            {
                return [json](MapObject* object)->void
                {
                    auto weaponComponent = object->get<WeaponComponent>();
                    assert(weaponComponent && "Object has to have a WeaponComponent");
                    if (weaponComponent)
                    {
                        std::string projectileTemplateName = json["projectile"].asString();
                        float fireRate = json["fireRate"].asFloat();
                        int nBullets = json["nProjectiles"].asInt();
                        
                        Weapon weapon(projectileTemplateName, fireRate);
                        if (weaponComponent->getWeapon() == weapon)
                        {
                            weaponComponent->addBullets(nBullets);
                        }
                        else
                        {
                            weaponComponent->reset(weapon, nBullets);
                        }
                    }
                };
            }
            
            const PowerUpAction* createPowerUpAction(const Json::Value& json)
            {
                static std::map<unsigned int, std::function<PowerUpFunction(const Json::Value&)>> lambdas = {
                    {Crypto::stringHash("Heal"), createHealFunction},
                    {Crypto::stringHash("Weapon"), createWeaponFunction},
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