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
#include <vector>
#include "Signal/Signal.h"

namespace MelonGames
{
    namespace KillyCraft
    {
        struct TextureMask
        {
            bool built = false;
            bool* mask = nullptr;
            int width = 0;
            int height = 0;
            
            ~TextureMask();
        };
        
        enum class CollisionDetectionType
        {
            ePlayer = 0,
            eEnemy,
            eBullet,
            ePowerup,
            
            nTypes
        };
        
        class CollisionDetectionComponent : public Component
        {
        public:
            DECLARE_TYPE_WITH_BASE_TYPE(CollisionDetectionComponent, Component);
            
            CollisionDetectionComponent();
            virtual ~CollisionDetectionComponent();
            
            void setType(CollisionDetectionType t);
            CollisionDetectionType getType() const;
            
            void addCollisionType(CollisionDetectionType type, bool collides=true);
            
            virtual void update(float dt) override;
            
            bool hasCollision() const;
            
            Gallant::Signal2<CollisionDetectionComponent*, CollisionDetectionComponent*>& getCollisionSignal();
            
        protected:
            bool ensureHasMask();
            void buildMask();
            
            bool collidesAgainst(CollisionDetectionComponent* other);
            
        private:
            TextureMask textureMask;
            bool pixelPerfect;
            CollisionDetectionType type;
            bool collisionTypes[(int)CollisionDetectionType::nTypes];
            
            std::vector<int> collisions;
            
            Gallant::Signal2<CollisionDetectionComponent*, CollisionDetectionComponent*> collisionSignal;
        };
    }
}

#endif /* defined(__KillyCraft__ViewOpacityMaskComponent__) */
