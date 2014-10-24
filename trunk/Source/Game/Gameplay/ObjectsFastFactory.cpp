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
#include "Component/GamepadMoveComponent.h"

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
				
				GamepadMoveComponent* gamepadMoveComponent = new GamepadMoveComponent();
				gamepadMoveComponent->setSpeed(100.0f, 100.0f);
				result->addComponent(gamepadMoveComponent);
				
				return result;
			}
			
			MapObject* createEnemyObject()
			{
				return nullptr;
			}
		}
	}
}