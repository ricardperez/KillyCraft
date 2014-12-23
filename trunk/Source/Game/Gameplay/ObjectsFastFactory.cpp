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
#include "Component/EnemyStateComponent.h"
#include "Component/PlayerLivesControllerComponent.h"

#include "Behaviour/MovementBehaviours.h"
#include "Behaviour/DestroyBehaviour.h"
#include "Behaviour/DestroyBehaviourFunctions.h"

#include "PowerUp/PowerUpAction.h"
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
				
				auto posComponent = new PositionComponent();
				posComponent->setPosition(cocos2d::Vec3(150.0f, 100.0f, 0.0f));
				result->addComponent(posComponent);
				
				auto viewComponent = new ViewComponent();
				viewComponent->setSpriteFrameName("Melon.png");
				result->addComponent(viewComponent);
                
                auto weaponComponent = new WeaponComponent();
                weaponComponent->setup(WeaponType::eMachinegun, 0.25f);
                result->addComponent(weaponComponent);
				
				auto gamepadComponent = new GamepadComponent();
				gamepadComponent->setSpeed(500.0f);
				result->addComponent(gamepadComponent);
                
                auto collisionDetection = new CollisionDetectionComponent();
                collisionDetection->setType(CollisionDetectionType::ePlayer);
                collisionDetection->addCollisionType(CollisionDetectionType::eEnemy);
                collisionDetection->addCollisionType(CollisionDetectionType::ePowerUp);
                collisionDetection->setCollisionMaskFileName("Melon.png.mask");
                result->addComponent(collisionDetection);
                
                auto playerLivesController = new PlayerLivesControllerComponent();
                result->addComponent(playerLivesController);
				
				return result;
			}
			
			MapObject* createEnemyObject()
			{
                MapObject* result = new MapObject();
                
                auto posComponent = new PositionComponent();
                posComponent->setPosition(cocos2d::Vec3(380.0f, 800.0f, 0.0f));
                result->addComponent(posComponent);
                
                auto viewComponent = new ViewComponent();
                viewComponent->setSpriteFrameName("Killy.png");
                result->addComponent(viewComponent);
                
                auto collisionDetection = new CollisionDetectionComponent();
                collisionDetection->setType(CollisionDetectionType::eEnemy);
                collisionDetection->setCollisionMaskFileName("Melon.png.mask");
                result->addComponent(collisionDetection);
                
                auto enemyState = new EnemyStateComponent();
                result->addComponent(enemyState);
                
                //Behaviour
                {
                    auto behaviourComponent = new BehaviourComponent();
                    auto linearMove = new MoveLinearBehaviour();
                    behaviourComponent->addBehaviour(linearMove);
                    
                    behaviourComponent->addBehaviour(new MoveCircularBehaviour());
                    
                    auto destroyBehaviour = new DestroyBehaviour();
                    destroyBehaviour->addCheckFunctionWithName(DestroyBehaviourFunctions::makeIsOutOfScreenDownFunction(), "OutOfScreen");
                    behaviourComponent->addBehaviour(destroyBehaviour);
                    
                    result->addComponent(behaviourComponent);
                    
                    auto circularState = new MoveCircularStateComponent();
                    circularState->setRadiansPerSecond(CC_DEGREES_TO_RADIANS(360.0f));
                    result->addComponent(circularState);
                }
                
                return result;
			}
            
            MapObject* createProjectile(MapObject* owner)
            {
                MapObject* result = new MapObject();
                
                auto posComponent = new PositionComponent();
                if (owner)
                {
                    const auto& shooterPosition = owner->get<PositionComponent>()->getPosition();
                    const auto& weaponOffset = owner->get<WeaponComponent>()->getRelativePosition();
                    posComponent->setPosition(shooterPosition + weaponOffset);
                }
                result->addComponent(posComponent);
                
                auto viewComponent = new ViewComponent();
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
                    auto behaviourComponent = new BehaviourComponent();
                    behaviourComponent->addBehaviour(new MoveLinearBehaviour());
                    
                    auto destroyBehaviour = new DestroyBehaviour();
                    destroyBehaviour->addCheckFunctionWithName(DestroyBehaviourFunctions::makeIsOutOfScreenUpFunction(), "bullet-OutOfScreen");
                    behaviourComponent->addBehaviour(destroyBehaviour);
                    
                    result->addComponent(behaviourComponent);
                }
                
                return result;
            }
		}
	}
}