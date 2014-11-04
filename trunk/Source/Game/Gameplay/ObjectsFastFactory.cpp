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

#include "Behaviour/MovementBehaviours.h"
#include "Behaviour/DestroyBehaviour.h"

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
				viewComponent->setSpriteFrameName("Killy.png");
				result->addComponent(viewComponent);
                
                WeaponComponent* weaponComponent = new WeaponComponent();
                weaponComponent->setup(WeaponType::eMachinegun, 0.25f);
                result->addComponent(weaponComponent);
				
				GamepadMoveComponent* gamepadMoveComponent = new GamepadMoveComponent();
				gamepadMoveComponent->setSpeed(500.0f, 500.0f);
				result->addComponent(gamepadMoveComponent);
                
                GamepadShootComponent* gamepadShootComponent = new GamepadShootComponent();
                result->addComponent(gamepadShootComponent);
				
				return result;
			}
			
			MapObject* createEnemyObject()
			{
                MapObject* result = new MapObject();
                
                auto posComponent = new PositionComponent();
                posComponent->setPosition(cocos2d::Vec3(380.0f, 800.0f, 0.0f));
                result->addComponent(posComponent);
                
                ViewComponent* viewComponent = new ViewComponent();
                viewComponent->setSpriteFrameName("Enemy1.png");
                result->addComponent(viewComponent);
                
                //Behaviour
                {
                    BehaviourComponent* behaviourComponent = new BehaviourComponent();
                    auto linearMove = new LinearMoveBehaviour();
                    behaviourComponent->addBehaviour(linearMove);
                    
                    behaviourComponent->addBehaviour(new CircularMoveBehaviour());
                    
                    DestroyBehaviour* destroyBehaviour = new DestroyBehaviour();
                    destroyBehaviour->addCheckFunctionWithName(DestroyBehaviourFunctions::isOutOfScreen, "OutOfScreen");
                    behaviourComponent->addBehaviour(destroyBehaviour);
                    
                    result->addComponent(behaviourComponent);
                    
                    CircularMoveStateComponent* circularState = new CircularMoveStateComponent();
                    circularState->setRadiansPerSecond(CC_DEGREES_TO_RADIANS(360.0f));
                    result->addComponent(circularState);
                }
                
                //Modifiers
                {
//                    result->addComponentModifier(ComponentModifiers::makeAccelerateLinearMovement(cocos2d::Vec3(0.0f, -10.0f, 0.0f), 3.0f));
//                    result->addComponentModifier(ComponentModifiers::makeAccelerateCircularMovement(CC_DEGREES_TO_RADIANS(45.0f), 5.0f));
                    result->addComponentModifier(ComponentModifiers::makeChangeRadiusForCircularMovement(150.0f, 50.0f, 30.0f));
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
                
                auto linearMoveState = new LinearMoveStateComponent();
                linearMoveState->setMovementPerSecond(cocos2d::Vec3(0.0f, 600.0f, 0.0f));
                result->addComponent(linearMoveState);
                
                //Behaviour
                {
                    BehaviourComponent* behaviourComponent = new BehaviourComponent();
                    behaviourComponent->addBehaviour(new LinearMoveBehaviour());
                    
                    DestroyBehaviour* destroyBehaviour = new DestroyBehaviour();
                    destroyBehaviour->addCheckFunctionWithName(DestroyBehaviourFunctions::isOutOfScreen, "OutOfScreen");
                    behaviourComponent->addBehaviour(destroyBehaviour);
                    
                    result->addComponent(behaviourComponent);
                }
                
                return result;
            }
		}
	}
}