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
#include "Gameplay/VFXController.h"
#include "ViewComponent.h"
#include "ViewParts.h"
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
        , invalidated(false)
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
            if (maskDrawer)
            {
                maskDrawer->removeFromParent();
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
        
        void CollisionDetectionComponent::preupdate()
        {
            Base::preupdate();
            
            collisionsPrevFrame = collisions;
            collisions.clear();
        }
        
        void CollisionDetectionComponent::postupdate()
        {
#ifdef DRAW_COLLISION_BOXES
            drawBox();
#endif
        }
        
        void CollisionDetectionComponent::update(float dt)
        {
            Base::update(dt);
            
            if (invalidated)
            {
                return;
            }
            
            bool particleSystemsInstantiated = false;
            const auto& objects = object->getMap()->getObjects();
            for (auto object : objects)
            {
                if (object != this->object)
                {
                    int oid = object->getIdentifier();
                    
                    bool isInBlackList = (std::find(ignoredObjectsIDs.begin(), ignoredObjectsIDs.end(), oid) != ignoredObjectsIDs.end());
                    if (isInBlackList)
                    {
                        break;
                    }
                    
                    bool alreadyCollided = (std::find(collisions.begin(), collisions.end(), oid) != collisions.end());
                    if (alreadyCollided)
                    {
                        break;
                    }
                    
                    if (auto other = object->get<CollisionDetectionComponent>())
                    {
                        if (collidesAgainst(other))
                        {
                            collisions.push_back(oid);
                            other->collisions.push_back(this->object->getIdentifier());
                            if (!particleSystemsInstantiated)
                            {
                                particleSystemsInstantiated = true;
                                instantiateParticleSystems();
                            }
                            collisionSignal.Emit(this, other);
                            
                            other->instantiateParticleSystems();
                            other->collisionSignal.Emit(other, this);
                        }
                    }
                }
            }
        }
        
        bool CollisionDetectionComponent::hasCollision() const
        {
            return (!collisions.empty() || !collisionsPrevFrame.empty());
        }
        
        Gallant::Signal2<CollisionDetectionComponent*, CollisionDetectionComponent*>& CollisionDetectionComponent::getCollisionSignal()
        {
            return collisionSignal;
        }
        
        void CollisionDetectionComponent::ignoreCollisionsAgainstObject(const MapObject* object)
        {
            ignoredObjectsIDs.push_back(object->getIdentifier());
        }
        
        void CollisionDetectionComponent::invalidate()
        {
            invalidated = true;
        }
        
        bool getRectsIntersection(const cocos2d::Rect& r1, const cocos2d::Rect& r2, cocos2d::Vec2& r1StartOut, cocos2d::Vec2& r2StartOut, cocos2d::Size& intersectionSizeOut)
        {
            if (r1.intersectsRect(r2))
            {
                cocos2d::Vec2 r1Start;
                cocos2d::Vec2 r1End;
                
                cocos2d::Vec2 r2Start;
                cocos2d::Vec2 r2End;
                
                float r1Left = r1.origin.x;
                float r1Right = r1.origin.x + r1.size.width;
                float r1Bottom = r1.origin.y;
                float r1Top = r1.origin.y + r1.size.height;
                
                float r2Left = r2.origin.x;
                float r2Right = r2.origin.x + r2.size.width;
                float r2Bottom = r2.origin.y;
                float r2Top = r2.origin.y + r2.size.height;
                
                if (r1Left < r2Left)
                {
                    r2Start.x = 0.0f;
                    r1Start.x = r2Left - r1Left;
                }
                else
                {
                    r1Start.x = 0.0f;
                    r2Start.x = r1Left - r2Left;
                }
                
                if (r1Bottom < r2Bottom)
                {
                    r2Start.y = 0.0f;
                    r1Start.y = r2Bottom - r1Bottom;
                }
                else
                {
                    r1Start.y = 0.0f;
                    r2Start.y = r1Bottom - r2Bottom;
                }
                
                if (r1Right > r2Right)
                {
                    r2End.x = r2.size.width;
                    r1End.x = r2Right - r1Left;
                }
                else
                {
                    r1End.x = r1.size.width;
                    r2End.x = r1Right - r2Left;
                }
                
                if (r1Top > r2Top)
                {
                    r2End.y = r2.size.height;
                    r1End.y = r2Top - r1Bottom;
                }
                else
                {
                    r1End.y = r1.size.height;
                    r2End.y = r1Top - r2Bottom;
                }
                
                r1StartOut = r1Start;
                r2StartOut = r2Start;
                
                float intersectionWidth = (r1End.x - r1Start.x);
                float intersectionHeight = (r1End.y - r1Start.y);
                intersectionSizeOut = cocos2d::Size(intersectionWidth, intersectionHeight);
                
                return true;
            }
            
            return false;
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
                textureMask = TextureMask::create(viewComponent->getSize());
            }
            
            maskBuilt = (textureMask != nullptr);
        }
        
        bool CollisionDetectionComponent::collidesAgainst(CollisionDetectionComponent* other)
        {
            if (other->invalidated)
            {
                return false;
            }
            
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
            const cocos2d::Vec2& position = object->get<PositionComponent>()->getPosition();

            cocos2d::Rect rect;
            if (textureMask)
            {
                rect.size = cocos2d::Vec2(textureMask->getWidth(), textureMask->getHeight());
            }
            rect.origin = position - rect.size*0.5f;
            
            return rect;
        }
        
        void CollisionDetectionComponent::instantiateParticleSystems()
        {
            if (!particleSystems.empty())
            {
                const auto& position = object->get<PositionComponent>()->getPosition();
                for (const auto& particleSystemData : particleSystems)
                {
                    if (particleSystemData.attached)
                    {
                        object->getMap()->getVFXController()->showParticleSystem(particleSystemData.plist, object);
                    }
                    else
                    {
                        object->getMap()->getVFXController()->showParticleSystem(particleSystemData.plist, position);
                    }
                }
            }
        }
        
#ifdef DRAW_COLLISION_BOXES
        void CollisionDetectionComponent::drawBox()
        {
            if (maskDrawer == nullptr)
            {
                maskDrawer = cocos2d::DrawNode::create();
                object->getMap()->getView()->getNode()->addChild(maskDrawer);
            }
            maskDrawer->clear();
            
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
                case CollisionDetectionType::ePowerUp:
                    color = cocos2d::Color4F::GREEN;
                    break;
                default:
                    color = cocos2d::Color4F::MAGENTA;
            }
            
            color.a = 0.5f;
            
            if (maskBuilt && textureMask->isPixelPerfect())
            {
                cocos2d::Vec2 position = object->get<ViewComponent>()->getSprite()->getPosition();
                cocos2d::Vec2 origin = (position - cocos2d::Vec2(textureMask->getWidth()*0.5f, textureMask->getHeight()*0.5f));
                
                int pointSize = 5;
                
                for (int x=0; x<textureMask->getWidth(); x+=pointSize)
                {
                    for (int y=0; y<textureMask->getHeight(); y+=pointSize)
                    {
                        if (textureMask->isOpaqueAt(x, y))
                        {
                            auto bl = origin + cocos2d::Vec2(x,y);
                            auto tr = bl + cocos2d::Vec2(pointSize, pointSize);
                            maskDrawer->drawSolidRect(bl, tr, color);
                        }
                    }
                }
            }
            else
            {
                auto rect = getCurrentRect();
                maskDrawer->drawRect(rect.origin, rect.origin + cocos2d::Vec2(rect.size.width, rect.size.height), color);
            }
        }
#endif
        
    }
}
