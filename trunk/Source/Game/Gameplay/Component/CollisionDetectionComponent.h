//
//  ViewOpacityMaskComponent.h
//  KillyCraft
//
//  Created by Ricard Perez del Campo on 02/11/14.
//  Copyright (c) 2014 MelonGames. All rights reserved.
//

#ifndef __KillyCraft__ViewOpacityMaskComponent__
#define __KillyCraft__ViewOpacityMaskComponent__

#include "Component.h"
#include "GameConfig.h"
#include "Signal/Signal.h"
#include "math/CCGeometry.h"
#include <vector>

namespace cocos2d
{
    class DrawNode;
}

namespace MelonGames
{
    namespace KillyCraft
    {
        class TextureMask;
        enum class CollisionDetectionType
        {
            ePlayer = 0,
            eEnemy,
            eBullet,
            ePowerUp,
            
            nTypes
        };
        
        class CollisionDetectionComponent : public Component
        {
        public:
            DECLARE_TYPE_WITH_BASE_TYPE(CollisionDetectionComponent, Component);
            
            CollisionDetectionComponent();
            virtual ~CollisionDetectionComponent();
            
            virtual void onWillDetachFromObject() override;
            
            void setType(CollisionDetectionType t);
            CollisionDetectionType getType() const;
            
            void setCollisionMaskFileName(const std::string& fileName);
            
            void addCollisionType(CollisionDetectionType type, bool collides=true);
            
            virtual void preupdate() override;
            virtual void update(float dt) override;
            
            bool hasCollision() const;
            
            Gallant::Signal1<CollisionDetectionComponent*>& getCollisionSignal();
            
        protected:
            bool ensureHasMask();
            void buildMask();
            
            bool collidesAgainst(CollisionDetectionComponent* other);
            
            cocos2d::Rect getCurrentRect() const;
            
        private:
            bool maskBuilt;
            std::string maskFileName;
            TextureMask* textureMask;
            CollisionDetectionType type;
            bool collisionTypes[(int)CollisionDetectionType::nTypes];
            
            std::vector<int> collisions;
            
            Gallant::Signal1<CollisionDetectionComponent*> collisionSignal;
            
#ifdef DRAW_COLLISION_BOXES
            cocos2d::DrawNode* boxDrawer = nullptr;
            unsigned int boxDrawerFrame = 0;
            void drawBox();
#endif
        };
    }
}

#endif /* defined(__KillyCraft__ViewOpacityMaskComponent__) */
