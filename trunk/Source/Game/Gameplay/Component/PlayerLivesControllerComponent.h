//
//  PlayerLivesControllerComponent.h
//  KillyCraft
//
//  Created by Ricard Perez del Campo on 23/12/14.
//  Copyright (c) 2014 MelonGames. All rights reserved.
//

#ifndef __KillyCraft__PlayerLivesControllerComponent__
#define __KillyCraft__PlayerLivesControllerComponent__

#include "Component.h"

namespace MelonGames
{
    namespace KillyCraft
    {
        class CollisionDetectionComponent;
        
        class PlayerLivesControllerComponent : public Component
        {
        public:
            DECLARE_TYPE_WITH_BASE_TYPE(PlayerLivesControllerComponent, Component);
            
            virtual void onObjectAttachedToMap() override;
            virtual void onWillDetachFromObject() override;
            
        private:
            void onPlayerCollision(CollisionDetectionComponent* playerCollisionDetection, CollisionDetectionComponent* otherCollisionDetection);
        };
    }
}

#endif /* defined(__KillyCraft__PlayerLivesControllerComponent__) */
