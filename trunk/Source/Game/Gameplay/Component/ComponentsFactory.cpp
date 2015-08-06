//
//  ComponentsFactory.cpp
//  KillyCraft
//
//  Created by Ricard Perez del Campo on 24/12/14.
//  Copyright (c) 2014 MelonGames. All rights reserved.
//

#include "ComponentsFactory.h"
#include "Gameplay/Behaviour/BehavioursFactory.h"
#include "Gameplay/PowerUp/PowerUpFactory.h"
#include "MelonGames/Crypto.h"

#include "PositionComponent.h"
#include "ViewComponent.h"
#include "ViewParts.h"
#include "GamepadComponent.h"
#include "WeaponComponent.h"
#include "BehaviourComponent.h"
#include "MovementStateComponents.h"
#include "CollisionDetectionComponent.h"
#include "PowerUpComponent.h"
#include "PlayerStateComponent.h"
#include "EnemyStateComponent.h"
#include "ProjectileStateComponent.h"
#include "ShieldComponent.h"

#include "math/Vec2.h"
#include "json/value.h"

namespace MelonGames
{
    namespace KillyCraft
    {
        namespace ComponentsFactory
        {
            cocos2d::Vec2 vec2FromJson(const Json::Value& json)
            {
                cocos2d::Vec2 result(json[0].asFloat(), json[1].asFloat());
                return result;
            }
            
            Component* createComponent(const Json::Value& json)
            {
                static std::map<unsigned int, std::function<Component*(const Json::Value&)>> lambdas = {
                    {Crypto::stringHash("Position"), createPositionComponent},
                    {Crypto::stringHash("View"), createViewComponent},
                    {Crypto::stringHash("Behaviour"), createBehaviourComponent},
                    {Crypto::stringHash("MoveCircular"), createMoveCircularStateComponent},
                    {Crypto::stringHash("MoveLinear"), createMoveLinearStateComponent},
                    {Crypto::stringHash("MoveIdle"), createMoveIdleStateComponent},
                    {Crypto::stringHash("CollisionDetection"), createCollisionDetectionComponent},
                    {Crypto::stringHash("PowerUp"), createPowerUpComponent},
                    {Crypto::stringHash("EnemyState"), createEnemyStateComponent},
                    {Crypto::stringHash("Weapon"), createWeaponComponent},
                    {Crypto::stringHash("Gamepad"), createGamepadComponent},
                    {Crypto::stringHash("PlayerState"), createPlayerStateComponent},
                    {Crypto::stringHash("ProjectileState"), createProjectileStateComponent},
                    {Crypto::stringHash("Shield"), createShieldComponent},
                };
                
                std::string type = json["type"].asString();
                unsigned int key = Crypto::stringHash(type);
                
                auto lambdaIt = lambdas.find(key);
                if (lambdaIt != lambdas.end())
                {
                    return lambdaIt->second(json);
                }
                
                CCASSERT(false, ("Could not create a component of type " + type).c_str());
                
                return nullptr;
            }

            Component* createPositionComponent(const Json::Value& json)
            {
                return new PositionComponent();
            }
            
            Component* createViewComponent(const Json::Value& json)
            {
                auto result = new ViewComponent();
                
                result->setRotateOnMovement(json["rotateOnMovement"].asBool());
                
                for (const auto& partJson : json["parts"])
                {
                    ViewPart* part = ViewPartsFactory::createViewPart(partJson);
                    if (part != nullptr)
                    {
                        result->addPart(part, true);
                    }
                    else
                    {
                        delete result;
                        return nullptr;
                    }
                }
                
                return result;
            }
            
            Component* createGamepadComponent(const Json::Value& json)
            {
                auto result = new GamepadComponent();
                float speed = json["speed"].asFloat();
                result->setSpeed(speed);
                return result;
            }
            
            Component* createWeaponComponent(const Json::Value& json)
            {
                auto result = new WeaponComponent();
                std::string projectileTemplateName = json["projectile"].asString();
                float fireRate = json["fireRate"].asFloat();
                int nBullets = json["nProjectiles"].asInt();
                result->reset(Weapon(projectileTemplateName, fireRate), nBullets);
                return result;
            }
            
            Component* createBehaviourComponent(const Json::Value& json)
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
            }
            
            Component* createMoveLinearStateComponent(const Json::Value& json)
            {
                auto result = new MoveLinearStateComponent();
                result->setMovementPerSecond(vec2FromJson(json["move"]));
                result->setBackgroundSpeedMultiplier(json["backgroundSpeedMultiplier"].asFloat());
                return result;
            }
            
            Component* createMoveCircularStateComponent(const Json::Value& json)
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
                
                result->setRadius(json["radius"].asFloat());
                return result;
            }
            
            Component* createMoveIdleStateComponent(const Json::Value& json)
            {
                auto result = new MoveIdleStateComponent();
                
                result->movementDistanceX = json["distX"].asFloat();
                result->movementDistanceY = json["distY"].asFloat();
                result->movementTime = json["time"].asFloat();
                result->gaussianA = json["gaussianA"].asFloat();
                result->gaussianC = json["gaussianC"].asFloat();
                result->gaussianXRange = json["gaussianXRange"].asFloat();
                
                return result;
            }
            
            Component* createCollisionDetectionComponent(const Json::Value& json)
            {
                auto result = new CollisionDetectionComponent();
                result->setCollisionMaskFileName(json["mask"].asString());
                result->setType((CollisionDetectionType)json["t"].asInt());
                for (const auto& collisionTypes : json["c"])
                {
                    result->addCollisionType((CollisionDetectionType)collisionTypes.asInt());
                }
                for (const auto& particleSystem : json["particles"])
                {
                    CollisionDetectionComponent::CollisionParticleSystemData psData;
                    psData.plist = particleSystem["plist"].asString();
                    result->particleSystems.push_back(psData);
                }
                return result;
            }
            
            Component* createPowerUpComponent(const Json::Value& json)
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
            }
            
            Component* createPlayerStateComponent(const Json::Value& json)
            {
                auto result = new PlayerStateComponent();
                return result;
            }
            
            Component* createEnemyStateComponent(const Json::Value& json)
            {
                auto result = new EnemyStateComponent();
                result->livesCost = json["livesCost"].asUInt();
                result->lives = json["lives"].asUInt();
                result->score = json["score"].asUInt();
                for (const auto& particleSystemName : json["dieParticles"])
                {
                    result->dieParticleSystems.push_back(particleSystemName.asString());
                }
                return result;
            }
            
            Component* createProjectileStateComponent(const Json::Value& json)
            {
                auto result = new ProjectileStateComponent();
                result->power = json["power"].asUInt();
                result->nCollisionsSupported = json["collisionsSupported"].asUInt();
                return result;
            }
            
            Component* createShieldComponent(const Json::Value& json)
            {
                auto result = new ShieldComponent();
                result->assetName = json["asset"].asString();
                return result;
            }
        }
    }
}