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

namespace MelonGames
{
    namespace KillyCraft
    {
        struct TextureMask
        {
            bool* mask = nullptr;
            int width = 0;
            int height = 0;
            
            ~TextureMask();
        };
        
        class CollisionDetectionComponent : public Component
        {
        public:
            DECLARE_TYPE_WITH_BASE_TYPE(CollisionDetectionComponent, Component);
            
            CollisionDetectionComponent();
            virtual ~CollisionDetectionComponent();
            
            bool collidesAgainst(CollisionDetectionComponent* other);
            
        protected:
            bool ensureHasMask();
            void buildMask();
            
        private:
            TextureMask textureMask;
            bool pixelPerfect;
        };
    }
}

#endif /* defined(__KillyCraft__ViewOpacityMaskComponent__) */
