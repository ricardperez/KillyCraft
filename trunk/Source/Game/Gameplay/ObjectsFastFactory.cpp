//
//  ObjectsFastFactory.cpp
//  KillyCraft
//
//  Created by Ricard Pérez del Campo on 21/10/14.
//
//

#include "ObjectsFastFactory.h"
#include "MapObject.h"
#include "Component/PositionComponent.h"
#include "Component/ViewComponent.h"
#include "Component/GamepadComponent.h"
#include "Component/WeaponComponent.h"
#include "Component/BehaviourComponent.h"
#include "Component/MovementStateComponents.h"
#include "Component/CollisionDetectionComponent.h"
#include "Component/PowerUpComponent.h"

#include "Behaviour/MovementBehaviours.h"
#include "Behaviour/DestroyBehaviour.h"
#include "Behaviour/DestroyBehaviourFunctions.h"

#include "PowerUp/PowerUp.h"
#include "PowerUp/PowerUpFactory.h"

#include "base/ccMacros.h"

namespace MelonGames
{
	namespace KillyCraft
	{
		namespace ObjectsFastFactory
		{
			MapObject* createPlayerObject()
			{
				MapObject* result = new MapObject();
				
				PositionComponent* posComponent = new PositionComponent();
				posComponent->setPosition(cocos2d::Vec3(150.0f, 100.0f, 0.0f));
				result->addComponent(posComponent);
				
				ViewComponent* viewComponent = new ViewComponent();
				viewComponent->setSpriteFrameName("Melon.png");
				result->addComponent(viewComponent);
                
                WeaponComponent* weaponComponent = new WeaponComponent();
                weaponComponent->setup(WeaponType::eMachinegun, 0.25f);
                result->addComponent(weaponComponent);
				
				GamepadMoveComponent* gamepadMoveComponent = new GamepadMoveComponent();
				gamepadMoveComponent->setSpeed(500.0f, 500.0f);
				result->addComponent(gamepadMoveComponent);
                
                GamepadShootComponent* gamepadShootComponent = new GamepadShootComponent();
                result->addComponent(gamepadShootComponent);
                
                auto collisionDetection = new CollisionDetectionComponent();
                collisionDetection->setType(CollisionDetectionType::ePlayer);
                collisionDetection->addCollisionType(CollisionDetectionType::eEnemy);
                collisionDetection->addCollisionType(CollisionDetectionType::ePowerUp);
                collisionDetection->setCollisionMaskFileName("Melon.png.mask");
                result->addComponent(collisionDetection);
				
				return result;
			}
			
			MapObject* createEnemyObject()
			{
                MapObject* result = new MapObject();
                
                auto posComponent = new PositionComponent();
                posComponent->setPosition(cocos2d::Vec3(380.0f, 800.0f, 0.0f));
                result->addComponent(posComponent);
                
                ViewComponent* viewComponent = new ViewComponent();
                viewComponent->setSpriteFrameName("Killy.png");
                result->addComponent(viewComponent);
                
                auto collisionDetection = new CollisionDetectionComponent();
                collisionDetection->setType(CollisionDetectionType::eEnemy);
                result->addComponent(collisionDetection);
                
                //Behaviour
                {
                    BehaviourComponent* behaviourComponent = new BehaviourComponent();
                    auto linearMove = new MoveLinearBehaviour();
                    behaviourComponent->addBehaviour(linearMove);
                    
                    behaviourComponent->addBehaviour(new MoveCircularBehaviour());
                    
                    DestroyBehaviour* destroyBehaviour = new DestroyBehaviour();
                    destroyBehaviour->addCheckFunctionWithName(DestroyBehaviourFunctions::makeIsOutOfScreenDownFunction(), "OutOfScreen");
                    behaviourComponent->addBehaviour(destroyBehaviour);
                    
                    result->addComponent(behaviourComponent);
                    
                    MoveCircularStateComponent* circularState = new MoveCircularStateComponent();
                    circularState->setRadiansPerSecond(CC_DEGREES_TO_RADIANS(360.0f));
                    result->addComponent(circularState);
                }
                
                return result;
			}
            
            MapObject* createProjectile(MapObject* owner)
            {
                MapObject* result = new MapObject();
                
                const auto& shooterPosition = owner->get<PositionComponent>()->getPosition();
                const auto& weaponOffset = owner->get<WeaponComponent>()->getRelativePosition();
                
                auto posComponent = new PositionComponent();
                posComponent->setPosition(shooterPosition + weaponOffset);
                result->addComponent(posComponent);
                
                ViewComponent* viewComponent = new ViewComponent();
                viewComponent->setSpriteFrameName("Bullet.png");
                result->addComponent(viewComponent);
                
                auto linearMoveState = new MoveLinearStateComponent();
                linearMoveState->setMovementPerSecond(cocos2d::Vec3(0.0f, 600.0f, 0.0f));
                result->addComponent(linearMoveState);
                
                auto collisionDetection = new CollisionDetectionComponent();
                collisionDetection->setType(CollisionDetectionType::eBullet);
                collisionDetection->addCollisionType(CollisionDetectionType::eEnemy);
                result->addComponent(collisionDetection);
                
                //Behaviour
                {
                    BehaviourComponent* behaviourComponent = new BehaviourComponent();
                    behaviourComponent->addBehaviour(new MoveLinearBehaviour());
                    
                    DestroyBehaviour* destroyBehaviour = new DestroyBehaviour();
                    destroyBehaviour->addCheckFunctionWithName(DestroyBehaviourFunctions::makeIsOutOfScreenUpFunction(), "OutOfScreen");
                    behaviourComponent->addBehaviour(destroyBehaviour);
                    
                    result->addComponent(behaviourComponent);
                }
                
                return result;
            }
            
            MapObject* createPowerUp()
            {
                MapObject* result = new MapObject();
                
                auto posComponent = new PositionComponent();
                result->addComponent(posComponent);
                
                PowerUpComponent* powerUpComponent = new PowerUpComponent();
                if (auto powerUp = PowerUpFactory::createPowerUp(Json::nullValue))
                {
                    powerUpComponent->addPowerUp(powerUp);
                }
                result->addComponent(powerUpComponent);
                
                auto collisionDetection = new CollisionDetectionComponent();
                collisionDetection->setType(CollisionDetectionType::ePowerUp);
                result->addComponent(collisionDetection);
                
                BehaviourComponent* behaviourComponent = new BehaviourComponent();
                behaviourComponent->addBehaviour(new MoveLinearBehaviour());
                behaviourComponent->addBehaviour(new MoveCircularProjectedBehaviour());
                DestroyBehaviour* destroyBehaviour = new DestroyBehaviour();
                destroyBehaviour->addCheckFunctionWithName(DestroyBehaviourFunctions::makeIsCollisionFunction(), "Collision");
                destroyBehaviour->addCheckFunctionWithName(DestroyBehaviourFunctions::makeIsOutOfScreenDownFunction(), "OutOfScreen");
                behaviourComponent->addBehaviour(destroyBehaviour);
                result->addComponent(behaviourComponent);
                
                auto viewComponent = new ViewComponent();
                viewComponent->setSpriteFrameName("PowerUp.png");
                result->addComponent(viewComponent);
                
                auto moveLinearState = new MoveLinearStateComponent();
                moveLinearState->setMovementPerSecond(cocos2d::Vec3(0.0f, -50.0f, 0.0f));
                result->addComponent(moveLinearState);
                
                auto moveCircularState = new MoveCircularStateComponent();
                moveCircularState->setPeriod(2.0f);
                moveCircularState->setRadius(75.0f);
                result->addComponent(moveCircularState);
                
                return result;
            }
		}
	}
}