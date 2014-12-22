//
//  SpriteFrameHelper.cpp
//  KillyCraft
//
//  Created by Ricard Perez del Campo on 22/12/14.
//  Copyright (c) 2014 MelonGames. All rights reserved.
//

#include "SpriteFrameHelper.h"
#include "2d/CCSpriteFrameCache.h"
#include "2d/CCSpriteFrame.h"
#include "base/CCDirector.h"
#include "renderer/CCTextureCache.h"

namespace MelonGames
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
        }
        
        return frame;
    }
}