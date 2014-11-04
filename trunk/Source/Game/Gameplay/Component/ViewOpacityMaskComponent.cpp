//
//  ViewOpacityMaskComponent.cpp
//  KillyCraft
//
//  Created by Ricard Perez del Campo on 02/11/14.
//  Copyright (c) 2014 MelonGames. All rights reserved.
//

#include "ViewOpacityMaskComponent.h"
#include "Gameplay/MapObject.h"
#include "ViewComponent.h"
#include "PositionComponent.h"
#include "2d/CCSprite.h"
#include "2d/CCSpriteFrame.h"
#include "2d/CCRenderTexture.h"
#include <limits>

namespace MelonGames
{
    namespace KillyCraft
    {
        namespace TextureMaskHelper
        {
            TextureMask buildTextureMask(cocos2d::Texture2D* texture, const cocos2d::Rect& rect)
            {
                TextureMask result;
                
                result.width = rect.size.width;
                result.height = rect.size.height;
                int maskSize = result.width * result.height;
                result.mask = new bool[maskSize];
                memset(result.mask, 0, maskSize);
                
                int next = 0;
                for (int i=0; i<result.width; ++i)
                {
                    for (int j=0; j<result.height; ++j)
                    {
                        /*
                         int x = rect.origin.x + i;
                         int y = rect.origin.y + j;
                         GLubyte pixelOpaity = pixelAt(texture, x, y).alpha();
                         result.mask[next] = (pixelOpacity > 0);
                         */
                        ++next;
                    }
                }
                
                return result;
            }
            
            void destroyTextureMask(TextureMask& textureMask)
            {
                delete[] textureMask.mask;
                textureMask.mask = nullptr;
                textureMask.width = 0;
                textureMask.height = 0;
            }
            
            bool isMaskedValue(const TextureMask& textureMask, int x, int y)
            {
                if (textureMask.mask && x >= 0 && x < textureMask.width && y >= 0 && y < textureMask.height)
                {
                    return textureMask.mask[textureMask.width * y + x];
                }
                
                return false;
            }
            
            bool textureMaskCollision(const TextureMask& tm1, const TextureMask& tm2, const cocos2d::Vec2& origin1, const cocos2d::Vec2& origin2, const cocos2d::Size& size)
            {
                for (int i=0; i<size.width; ++i)
                {
                    for (int j=0; j<size.height; ++j)
                    {
                        bool masked1 = TextureMaskHelper::isMaskedValue(tm1, origin1.x + i, origin1.y + j);
                        if (masked1)
                        {
                            bool masked2 = TextureMaskHelper::isMaskedValue(tm2, origin2.x + i, origin2.y + j);
                            if (masked2)
                            {
                                return true;
                            }
                        }
                    }
                }
                return false;
            }
        }
        
        ViewOpacityMaskComponent::ViewOpacityMaskComponent()
        {
        }
        
        ViewOpacityMaskComponent::~ViewOpacityMaskComponent()
        {
            TextureMaskHelper::destroyTextureMask(textureMask);
        }
        
        
        bool rectsIntersection(const cocos2d::Rect& r1, const cocos2d::Rect& r2, cocos2d::Vec2& r1OriginOut, cocos2d::Vec2& r2OriginOut, cocos2d::Size& sizeOut)
        {
            auto lambda = [](const cocos2d::Rect& outterRect, const cocos2d::Rect& innerRect, cocos2d::Vec2& outterOriginOut, cocos2d::Vec2& innerOriginOut, cocos2d::Size& intersectionSizeOut)
            {
                innerOriginOut = cocos2d::Vec2(0.0f, 0.0f);
                outterOriginOut = innerRect.origin - outterRect.origin;
                intersectionSizeOut.width = std::min(innerRect.size.width, outterRect.size.width - outterOriginOut.x);
                intersectionSizeOut.height = std::min(innerRect.size.height, outterRect.size.height - outterOriginOut.y);
            };
            
            if (r1.containsPoint(r2.origin))
            {
                lambda(r1, r2, r1OriginOut, r2OriginOut, sizeOut);
                return true;
            }
            else if (r2.containsPoint(r1.origin))
            {
                lambda(r2, r1, r2OriginOut, r1OriginOut, sizeOut);
                return true;
            }
            
            return false;
        }
        
        bool ViewOpacityMaskComponent::collidesAgainst(ViewOpacityMaskComponent* other)
        {
            if (!ensureHasMask())
            {
                return false;
            }
            
            if (!other->ensureHasMask())
            {
                return false;
            }
            
            const TextureMask& otherTextureMask = other->textureMask;
            
            cocos2d::Vec2 selfPosition = object->get<PositionComponent>()->getGroundPosition();
            cocos2d::Vec2 otherPosition = other->getObject()->get<PositionComponent>()->getGroundPosition();
            
            cocos2d::Rect selfRect;
            selfRect.size = cocos2d::Vec2(textureMask.width, textureMask.height);
            selfRect.origin = selfPosition - selfRect.size*0.5f;
            
            cocos2d::Rect otherRect;
            otherRect.size = cocos2d::Vec2(otherTextureMask.width, otherTextureMask.height);
            otherRect.origin = otherPosition - otherRect.size*0.5f;
            
            cocos2d::Vec2 selfOrigin;
            cocos2d::Vec2 otherOrigin;
            cocos2d::Size intersectionSize;
            if (rectsIntersection(selfRect, otherRect, selfOrigin, otherOrigin, intersectionSize))
            {
                return TextureMaskHelper::textureMaskCollision(textureMask, otherTextureMask, selfOrigin, otherOrigin, intersectionSize);
            }
            
            return false;
        }
        
        bool ViewOpacityMaskComponent::ensureHasMask()
        {
            if (!textureMask.mask)
            {
                buildMask();
                return (textureMask.mask != nullptr);
            }
            
            return true;
        }
        
        void ViewOpacityMaskComponent::buildMask()
        {
            assert(!textureMask.mask);
            
            ViewComponent* viewComponent = object->get<ViewComponent>();
            if (cocos2d::Sprite* sprite = viewComponent->getSprite())
            {
                if (auto spriteFrame = sprite->getSpriteFrame())
                {
                    const cocos2d::Rect& rect = spriteFrame->getRectInPixels();
                    textureMask = TextureMaskHelper::buildTextureMask(sprite->getTexture(), rect);
                }
                else
                {
                    cocos2d::Rect rect;
                    rect.size = sprite->getTexture()->getContentSizeInPixels();
                    textureMask = TextureMaskHelper::buildTextureMask(sprite->getTexture(), rect);
                }
            }
        }
        
        
    }
}