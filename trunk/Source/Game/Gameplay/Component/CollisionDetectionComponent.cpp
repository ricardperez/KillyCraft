//
//  ViewOpacityMaskComponent.cpp
//  KillyCraft
//
//  Created by Ricard Perez del Campo on 02/11/14.
//  Copyright (c) 2014 MelonGames. All rights reserved.
//

#include "CollisionDetectionComponent.h"
#include "TextureMask.h"
#include "Gameplay/MapObject.h"
#include "Gameplay/Map.h"
#include "Gameplay/View/MapView.h"
#include "ViewComponent.h"
#include "PositionComponent.h"
#include "2d/CCSprite.h"
#include "2d/CCSpriteFrame.h"
#include "2d/CCRenderTexture.h"
#include "2d/CCDrawNode.h"
#include "CCDirector.h"
#include <limits>

namespace MelonGames
{
    namespace KillyCraft
    {
        CollisionDetectionComponent::CollisionDetectionComponent()
        : maskBuilt(false)
        , type(CollisionDetectionType::eEnemy)
        , textureMask(nullptr)
        {
            for (int i=0; i<(int)CollisionDetectionType::nTypes; ++i)
            {
                collisionTypes[i] = false;
            }
        }
        
        CollisionDetectionComponent::~CollisionDetectionComponent()
        {
        }
        
        void CollisionDetectionComponent::onWillDetachFromObject()
        {
#ifdef DRAW_COLLISION_BOXES
            if (boxDrawer)
            {
                boxDrawer->removeFromParent();
            }
#endif
            Base::onWillDetachFromObject();
        }
        
        void CollisionDetectionComponent::setType(CollisionDetectionType t)
        {
            type = t;
        }
        
        CollisionDetectionType CollisionDetectionComponent::getType() const
        {
            return type;
        }
        
        void CollisionDetectionComponent::setCollisionMaskFileName(const std::string& fileName)
        {
            maskFileName = fileName;
        }
        
        void CollisionDetectionComponent::addCollisionType(CollisionDetectionType type, bool collides)
        {
            collisionTypes[(int)type] = collides;
        }
        
        void CollisionDetectionComponent::update(float dt)
        {
            Base::update(dt);
            
#ifdef DRAW_COLLISION_BOXES
            drawBox();
#endif
        
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
#ifdef DRAW_COLLISION_BOXES
                            other->drawBox();
#endif
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
            auto aContainsB = [](const cocos2d::Rect& r1, const cocos2d::Rect& r2)->bool
            {
                cocos2d::Vec2 bl = r2.origin;
                cocos2d::Vec2 br(bl.x + r2.size.width, bl.y);
                cocos2d::Vec2 tl(bl.x, bl.y + r2.size.height);
                cocos2d::Vec2 tr(br.x, tl.y);
                
                return (r1.containsPoint(bl) || r1.containsPoint(br) || r1.containsPoint(tl) || r1.containsPoint(tr));
            };
            
            return (aContainsB(r1, r2) || aContainsB(r2, r1));
        }
        
        bool getRectsIntersection(const cocos2d::Rect& r1, const cocos2d::Rect& r2, cocos2d::Vec2& r1StartOut, cocos2d::Vec2& r2StartOut, cocos2d::Size& intersectionSizeOut)
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
            
            auto selfRect = getCurrentRect();
            auto otherRect = other->getCurrentRect();
            
            cocos2d::Vec2 selfOrigin;
            cocos2d::Vec2 otherOrigin;
            cocos2d::Size intersectionSize;
            if (getRectsIntersection(selfRect, otherRect, selfOrigin, otherOrigin, intersectionSize))
            {
                if (textureMask->isPixelPerfect() && other->textureMask->isPixelPerfect())
                {
                    return TextureMaskHelper::textureMaskCollision(*textureMask, *other->textureMask, selfOrigin, otherOrigin, intersectionSize);
                }
                
                if (textureMask->isPixelPerfect())
                {
                    return TextureMaskHelper::textureMaskCollision(*textureMask, selfOrigin, otherOrigin, intersectionSize);
                }
                
                if (other->textureMask->isPixelPerfect())
                {
                    return TextureMaskHelper::textureMaskCollision(*other->textureMask, otherOrigin, selfOrigin, intersectionSize);
                }
                
                return true;
            }
            
            return false;
        }
        
        cocos2d::Rect CollisionDetectionComponent::getCurrentRect() const
        {
            auto position = object->get<PositionComponent>()->getGroundPosition();
            float scale = 1.0f;
            if (auto view = object->get<ViewComponent>())
            {
                scale = view->getScale();
            }
            cocos2d::Rect rect;
            if (textureMask)
            {
                rect.size = cocos2d::Vec2(textureMask->getWidth() * scale, textureMask->getHeight() * scale);
            }
            rect.origin = position - rect.size*0.5f;
            
            return rect;
        }
        
        bool CollisionDetectionComponent::ensureHasMask()
        {
            if (!maskBuilt)
            {
                buildMask();
            }
            
            return true;
        }
        
        void CollisionDetectionComponent::buildMask()
        {
            assert(!maskBuilt);
            
            textureMask = TextureMask::create(maskFileName);
            if (!textureMask)
            {
                ViewComponent* viewComponent = object->get<ViewComponent>();
                if (cocos2d::Sprite* sprite = viewComponent->getSprite())
                {
                    cocos2d::Size size;
                    if (auto spriteFrame = sprite->getSpriteFrame())
                    {
                        size = spriteFrame->getRectInPixels().size;
                    }
                    else
                    {
                        size = sprite->getTexture()->getContentSizeInPixels();
                    }
                    
                    textureMask = TextureMask::create(size);
                }
            }
            
            maskBuilt = (textureMask != nullptr);
        }
        
#ifdef DRAW_COLLISION_BOXES
        void CollisionDetectionComponent::drawBox()
        {
            unsigned int currFrameIndex = cocos2d::Director::getInstance()->getTotalFrames();
            if (currFrameIndex != boxDrawerFrame)
            {
                boxDrawerFrame = currFrameIndex;
                if (boxDrawer)
                {
                    boxDrawer->removeFromParent();
                }
                
                boxDrawer = cocos2d::DrawNode::create();
                object->getMap()->getView()->getNode()->addChild(boxDrawer);
                
                auto rect = getCurrentRect();
                
                cocos2d::Color4F color;
                switch (type)
                {
                    case CollisionDetectionType::ePlayer:
                        color = cocos2d::Color4F::RED;
                        break;
                    case CollisionDetectionType::eEnemy:
                        color = cocos2d::Color4F::BLUE;
                        break;
                    case CollisionDetectionType::eBullet:
                        color = cocos2d::Color4F::ORANGE;
                        break;
                    case CollisionDetectionType::ePowerup:
                        color = cocos2d::Color4F::GREEN;
                        break;
                    default:
                        color = cocos2d::Color4F::MAGENTA;
                }
                
                boxDrawer->drawRect(rect.origin, rect.origin + cocos2d::Vec2(rect.size.width, rect.size.height), color);
            }
        }
#endif
        
    }
}
