//
//  ViewComponent.cpp
//  KillyCraft
//
//  Created by Ricard Pérez del Campo on 16/10/14.
//
//

#include "ViewComponent.h"
#include "MelonGames/SpriteFrameHelper.h"
#include "Gameplay/MapObject.h"
#include "Gameplay/Map.h"
#include "Gameplay/View/MapView.h"
#include "PositionComponent.h"
#include "2d/CCSprite.h"
#include "2d/CCSpriteFrame.h"

namespace MelonGames
{
	namespace KillyCraft
	{
		ViewComponent::ViewComponent()
		: sprite(nullptr)
        , tint(255, 255, 255)
		{
		}
		
		ViewComponent::~ViewComponent()
		{
			
		}
		
		void ViewComponent::onObjectAttachedToMap()
		{
			Base::onObjectAttachedToMap();
			
			sprite = cocos2d::Sprite::createWithSpriteFrame(spriteFrameOrDefault(spriteFrameName));
            sprite->setColor(tint);
			object->getMap()->getView()->getNode()->addChild(sprite);
			
			auto posComponent = object->get<PositionComponent>();
			posComponent->getPositionChangedSignal().Connect(this, &ViewComponent::onPositionChanged);
			if (posComponent->isPositionSet())
			{
				onPositionChanged(posComponent);
			}
			
		}
        
        void ViewComponent::onWillDetachFromObject()
        {
            if (sprite)
            {
                sprite->removeFromParent();
                sprite = nullptr;
            }
            Base::onWillDetachFromObject();
        }
        
        const cocos2d::Sprite* ViewComponent::getSprite() const
        {
            return sprite;
        }
        
        float ViewComponent::getScale() const
        {
            if (sprite)
            {
                return sprite->getScale();
            }
            return 0.0f;
        }
        
        void ViewComponent::setTintColor(const cocos2d::Color3B& color)
        {
            tint = color;
            if (sprite)
            {
                sprite->setColor(tint);
            }
        }
        
        const cocos2d::Color3B& ViewComponent::getTintColor() const
        {
            return tint;
        }
		
		void ViewComponent::onPositionChanged(PositionComponent* posComponent)
		{
			if (sprite)
			{
				sprite->setPosition(Perspective::screenPosition(posComponent->getPosition()));
			}
		}
	}
}