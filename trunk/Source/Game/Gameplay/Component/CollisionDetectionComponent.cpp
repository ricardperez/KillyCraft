//
//  ViewOpacityMaskComponent.cpp
//  KillyCraft
//
//  Created by Ricard Perez del Campo on 02/11/14.
//  Copyright (c) 2014 MelonGames. All rights reserved.
//

#include "CollisionDetectionComponent.h"
#include "Gameplay/MapObject.h"
#include "Gameplay/Map.h"
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
                
//                int maskSize = result.width * result.height;
//                result.mask = new bool[maskSize];
//                memset(result.mask, 0, maskSize);
//                
//                int next = 0;
//                for (int i=0; i<result.width; ++i)
//                {
//                    for (int j=0; j<result.height; ++j)
//                    {
//                        /*
//                         int x = rect.origin.x + i;
//                         int y = rect.origin.y + j;
//                         GLubyte pixelOpaity = pixelAt(texture, x, y).alpha();
//                         result.mask[next] = (pixelOpacity > 0);
//                         */
//                        ++next;
//                    }
//                }
                
                result.built = true;
                
                return result;
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
        
        TextureMask::~TextureMask()
        {
            delete[] mask;
        }
        
        CollisionDetectionComponent::CollisionDetectionComponent()
        : pixelPerfect(false)
        , type(CollisionDetectionType::eEnemy)
        {
            for (int i=0; i<(int)CollisionDetectionType::nTypes; ++i)
            {
                collisionTypes[i] = false;
            }
        }
        
        CollisionDetectionComponent::~CollisionDetectionComponent()
        {
        }
        
        void CollisionDetectionComponent::setType(CollisionDetectionType t)
        {
            type = t;
        }
        
        CollisionDetectionType CollisionDetectionComponent::getType() const
        {
            return type;
        }
        
        void CollisionDetectionComponent::addCollisionType(CollisionDetectionType type, bool collides)
        {
            collisionTypes[(int)type] = collides;
        }
        
        void CollisionDetectionComponent::update(float dt)
        {
            Base::update(dt);
            
            collisions.clear();
            const auto& objects = object->getMap()->getObjects();
            for (auto object : objects)
            {
                if (object != this->object)
                {
                    int oid = object->getIdentifier();
                    if (std::find(collisions.begin(), collisions.end(), oid) == collisions.end())
                    {
                        if (auto other = object->get<CollisionDetectionComponent>())
                        {
                            if (collidesAgainst(other))
                            {
                                collisions.push_back(oid);
                                other->collisions.push_back(this->object->getIdentifier());
                            }
                        }
                    }
                }
            }
        }
        
        bool CollisionDetectionComponent::hasCollision() const
        {
            return (!collisions.empty());
        }
        
        Gallant::Signal2<CollisionDetectionComponent*, CollisionDetectionComponent*>& CollisionDetectionComponent::getCollisionSignal()
        {
            return collisionSignal;
        }
        
        bool rectIntersectsWithRect(const cocos2d::Rect& r1, const cocos2d::Rect& r2)
        {
            cocos2d::Vec2 bl = r2.origin;
            cocos2d::Vec2 br(bl.x + r2.size.width, bl.y);
            cocos2d::Vec2 tl(bl.x, bl.y + r2.size.height);
            cocos2d::Vec2 tr(br.x, tl.y);
            
            return (r1.containsPoint(bl) || r1.containsPoint(br) || r1.containsPoint(tl) || r1.containsPoint(tr));
        }
        
        bool rectsIntersection(const cocos2d::Rect& r1, const cocos2d::Rect& r2, cocos2d::Vec2& r1StartOut, cocos2d::Vec2& r2StartOut, cocos2d::Size& intersectionSizeOut)
        {
            if (rectIntersectsWithRect(r1, r2))
            {
                float r1StartX;
                float r2StartX;
                
                float r1StartY;
                float r2StartY;
                
                float sizeWidth;
                float sizeHeight;
                
                if (r2.origin.x > r1.origin.x)
                {
                    r1StartX = r2.origin.x - r1.origin.x;
                    r2StartX = 0.0f;
                    sizeWidth = r1.origin.x + r1.size.width - r2.origin.x;
                }
                else
                {
                    r2StartX = r1.origin.x - r2.origin.x;
                    r1StartX = 0.0f;
                    sizeWidth = r2.origin.x + r2.size.width - r1.origin.x;
                }
                
                
                if (r2.origin.y > r1.origin.y)
                {
                    r1StartY = r2.origin.y - r1.origin.y;
                    r2StartY = 0.0f;
                    sizeHeight = r1.origin.y + r1.size.height - r2.origin.y;
                }
                else
                {
                    r2StartY = r1.origin.y - r2.origin.y;
                    r1StartY = 0.0f;
                    sizeHeight = r2.origin.y + r2.size.height - r1.origin.y;
                }
                
                r1StartOut = cocos2d::Vec2(r1StartX, r1StartY);
                r2StartOut = cocos2d::Vec2(r2StartX, r2StartY);
                intersectionSizeOut = cocos2d::Size(sizeWidth, sizeHeight);
                
                return true;
            }
            
            return false;
        }
        
        bool CollisionDetectionComponent::collidesAgainst(CollisionDetectionComponent* other)
        {
            if (!collisionTypes[(int)other->type])
            {
                return false;
            }
            
            if (!ensureHasMask())
            {
                return false;
            }
            
            if (!other->ensureHasMask())
            {
                return false;
            }
            
            cocos2d::Vec2 selfPosition = object->get<PositionComponent>()->getGroundPosition();
            cocos2d::Vec2 otherPosition = other->getObject()->get<PositionComponent>()->getGroundPosition();
            
            cocos2d::Rect selfRect;
            selfRect.size = cocos2d::Vec2(textureMask.width, textureMask.height);
            selfRect.origin = selfPosition - selfRect.size*0.5f;
            
            cocos2d::Rect otherRect;
            otherRect.size = cocos2d::Vec2(other->textureMask.width, other->textureMask.height);
            otherRect.origin = otherPosition - otherRect.size*0.5f;
            
            if (pixelPerfect && other->pixelPerfect)
            {
                cocos2d::Vec2 selfOrigin;
                cocos2d::Vec2 otherOrigin;
                cocos2d::Size intersectionSize;
                if (rectsIntersection(selfRect, otherRect, selfOrigin, otherOrigin, intersectionSize))
                {
                    if (pixelPerfect && other->pixelPerfect)
                    {
                        return TextureMaskHelper::textureMaskCollision(textureMask, other->textureMask, selfOrigin, otherOrigin, intersectionSize);
                    }
                    return true;
                }
            }
            else
            {
                return rectIntersectsWithRect(selfRect, otherRect);
            }
            
            return false;
        }
        
        bool CollisionDetectionComponent::ensureHasMask()
        {
            if (!textureMask.built)
            {
                buildMask();
                return (textureMask.built);
            }
            
            return true;
        }
        
        void CollisionDetectionComponent::buildMask()
        {
            assert(!textureMask.built);
            
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
                
                pixelPerfect = (textureMask.mask != nullptr);
            }
        }
        
        
    }
}