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
				posComponent->setPosition(cocos2d::Vec3(150.0f, 60.0f, 0.0f));
				result->addComponent(posComponent);
				
				ViewComponent* viewComponent = new ViewComponent();
				viewComponent->setSpriteFrameName("Killy.png");
				result->addComponent(viewComponent);
                
                WeaponComponent* weaponComponent = new WeaponComponent();
                weaponComponent->setup(WeaponType::eMachinegun, 0.25f);
                result->addComponent(weaponComponent);
				
				GamepadMoveComponent* gamepadMoveComponent = new GamepadMoveComponent();
				gamepadMoveComponent->setSpeed(100.0f, 100.0f);
				result->addComponent(gamepadMoveComponent);
                
                GamepadShootComponent* gamepadShootComponent = new GamepadShootComponent();
                result->addComponent(gamepadShootComponent);
				
				return result;
			}
			
			MapObject* createEnemyObject()
			{
                MapObject* result = new MapObject();
                
                return result;
			}
            
            MapObject* createProjectile(MapObject* owner)
            {
                MapObject* result = new MapObject();
                
                ViewComponent* viewComponent = new ViewComponent();
                viewComponent->setSpriteFrameName("Bullet.png");
                result->addComponent(viewComponent);
                
                return result;
            }
		}
	}
}