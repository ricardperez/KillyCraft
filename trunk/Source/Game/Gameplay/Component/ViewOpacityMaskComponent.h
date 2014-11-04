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
        };
        
        class ViewOpacityMaskComponent : public Component
        {
        public:
            DECLARE_TYPE_WITH_BASE_TYPE(ViewOpacityMaskComponent, Component);
            
            ViewOpacityMaskComponent();
            virtual ~ViewOpacityMaskComponent();
            
            bool collidesAgainst(ViewOpacityMaskComponent* other);
            
        protected:
            bool ensureHasMask();
            void buildMask();
            
        private:
            TextureMask textureMask;
        };
    }
}

#endif /* defined(__KillyCraft__ViewOpacityMaskComponent__) */
