//
//  ViewComponent.cpp
//  KillyCraft
//
//  Created by Ricard Pérez del Campo on 16/10/14.
//
//

#include "ViewComponent.h"
#include "Gameplay/MapObject.h"
#include "Gameplay/Map.h"
#include "Gameplay/View/MapView.h"
#include "PositionComponent.h"
#include "2d/CCSprite.h"
#include "2d/CCSpriteFrame.h"
#include "2d/CCSpriteFrameCache.h"
#include "renderer/CCTextureCache.h"
#include "base/CCDirector.h"

namespace MelonGames
{
	namespace KillyCraft
	{
		namespace CocosUtil
		{
			cocos2d::SpriteFrame* spriteFrameOrDefault(const std::string& name)
			{
				cocos2d::SpriteFrame* frame = cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName(name);
				if (frame == nullptr)
				{
					cocos2d::Texture2D* texture = cocos2d::Director::getInstance()->getTextureCache()->addImage(name);
					if (texture)
					{
						cocos2d::Rect rect;
						rect.size = texture->getContentSize();
						frame = cocos2d::SpriteFrame::createWithTexture(texture, rect);
					}
					else
					{
						frame = cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName("placeholder.png");
						if (frame == nullptr)
						{
							cocos2d::Texture2D* texture = cocos2d::Director::getInstance()->getTextureCache()->addImage("placeholder.png");
							if (texture)
							{
								cocos2d::Rect rect;
								rect.size = texture->getContentSize();
								frame = cocos2d::SpriteFrame::createWithTexture(texture, rect);
							}
						}
					}
				}
				
				return frame;
			}
		}
		
		ViewComponent::ViewComponent()
		: sprite(nullptr)
		{
		}
		
		ViewComponent::~ViewComponent()
		{
			
		}
		
		void ViewComponent::setSpriteFrameName(const std::string &name)
		{
			spriteFrameName = name;
		}
		
		void ViewComponent::onObjectAttachedToMap()
		{
			Base::onObjectAttachedToMap();
			
			sprite = cocos2d::Sprite::createWithSpriteFrame(CocosUtil::spriteFrameOrDefault(spriteFrameName));
			object->getMap()->getView()->getNode()->addChild(sprite);
			
			auto posComponent = object->get<PositionComponent>();
			posComponent->getPositionChangedSignal().Connect(this, &ViewComponent::onPositionChanged);
			if (posComponent->isPositionSet())
			{
				onPositionChanged(posComponent);
			}
			
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