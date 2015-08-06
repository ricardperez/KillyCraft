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
        namespace ComponentsFactory
        {
            Component* createCollisionDetectionComponent(const Json::Value& json);
        }
        
        class TextureMask;
        enum class CollisionDetectionType
        {
            ePlayer = 0,
            eEnemy = 1,
            eBullet = 2,
            ePowerUp = 3,
            eEnemyBullet = 4,
            
            nTypes
        };
        
        class CollisionDetectionComponent : public Component
        {
        public:
            DECLARE_TYPE_WITH_BASE_TYPE(CollisionDetectionComponent, Component);
            
            friend Component* ComponentsFactory::createCollisionDetectionComponent(const Json::Value& json);
            
            CollisionDetectionComponent();
            virtual ~CollisionDetectionComponent();
            
            virtual void onWillDetachFromObject() override;
            
            CollisionDetectionType getType() const;
            
            void addCollisionType(CollisionDetectionType type, bool collides=true);
            
            virtual void preupdate() override;
            virtual void update(float dt) override;
            virtual void postupdate() override;
            
            bool hasCollision() const;
            
            Gallant::Signal2<CollisionDetectionComponent*,CollisionDetectionComponent*>& getCollisionSignal();
            
            void ignoreCollisionsAgainstObject(const MapObject* object);
            
            void invalidate();
            
        private:
            void setType(CollisionDetectionType t);
            void setCollisionMaskFileName(const std::string& fileName);
            
        protected:
            bool ensureHasMask();
            void buildMask();
            bool collidesAgainst(CollisionDetectionComponent* other);
            cocos2d::Rect getCurrentRect() const;
            void instantiateParticleSystems();
            
        private:
            bool maskBuilt;
            std::string maskFileName;
            TextureMask* textureMask;
            CollisionDetectionType type;
            bool collisionTypes[(int)CollisionDetectionType::nTypes];
            
            std::vector<int> collisions;
            std::vector<int> collisionsPrevFrame;
            
            Gallant::Signal2<CollisionDetectionComponent*,CollisionDetectionComponent*> collisionSignal;
            
            std::vector<int> ignoredObjectsIDs;
            
            struct CollisionParticleSystemData
            {
                std::string plist;
            };
            std::vector<CollisionParticleSystemData> particleSystems;
            
            bool invalidated;
            
#ifdef DRAW_COLLISION_BOXES
            cocos2d::DrawNode* maskDrawer = nullptr;
            void drawBox();
#endif
        };
    }
}

#endif /* defined(__KillyCraft__ViewOpacityMaskComponent__) */
