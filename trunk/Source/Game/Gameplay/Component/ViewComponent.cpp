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
                    if (cocos2d::Texture2D* texture = cocos2d::Director::getInstance()->getTextureCache()->addImage(name))
                    {
                        cocos2d::Rect rect;
                        rect.size = texture->getContentSize();
                        frame = cocos2d::SpriteFrame::createWithTexture(texture, rect);
                    }
                    else
                    {
                        CCLOG("Can't create a texture with file %s", name.c_str());
                    }
				}
                
                if (frame == nullptr && name != "placeholder.png")
                {
                    frame = spriteFrameOrDefault("placeholder.png");
                }
                
                if (frame == nullptr)
                {
                    static cocos2d::Texture2D* texture = nullptr;
                    if (texture == nullptr)
                    {
                        texture = new cocos2d::Texture2D();
                        const int size = 64;
                        int nElements = size*size*4;
                        GLubyte buffer[nElements];
                        memset(buffer, 255, nElements);
                        texture->initWithData(buffer, 4, cocos2d::Texture2D::PixelFormat::RGBA8888, size, size, cocos2d::Size(size, size));
                    }
                    
                    cocos2d::Rect rect;
                    rect.size = texture->getContentSize();
                    frame = cocos2d::SpriteFrame::createWithTexture(texture, rect);
                    
                    //[[CCTexture2D alloc] initWithData:buffer pixelFormat:kCCTexture2DPixelFormat_RGB5A1 pixelsWide:1 pixelsHigh:1 contentSize:size];
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
        
        void ViewComponent::onWillDetachFromObject()
        {
            if (sprite)
            {
                sprite->removeFromParent();
                sprite = nullptr;
            }
            Base::onWillDetachFromObject();
        }
        
        void ViewComponent::setSpriteFrameName(const std::string &name)
        {
            spriteFrameName = name;
        }
        
        cocos2d::Sprite* ViewComponent::getSprite() const
        {
            return sprite;
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