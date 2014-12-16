//
//  PowerUpComponent.h
//  KillyCraft
//
//  Created by Ricard Perez del Campo on 14/12/14.
//  Copyright (c) 2014 MelonGames. All rights reserved.
//

#ifndef __KillyCraft__PowerUpComponent__
#define __KillyCraft__PowerUpComponent__

#include "Component.h"
#include <vector>

namespace MelonGames
{
    namespace KillyCraft
    {
        class PowerUp;
        class CollisionDetectionComponent;
        
        class PowerUpComponent : public Component
        {
        public:
            DECLARE_TYPE_WITH_BASE_TYPE(PowerUpComponent, Component);
            
            PowerUpComponent();
            
            virtual void onObjectAttachedToMap() override;
            virtual void onWillDetachFromObject() override;
            
            void addPowerUp(const PowerUp* powerUp);
            
        private:
            void onCollisionDetection(CollisionDetectionComponent* otherCollisionComponent);
            
        private:
            std::vector<const PowerUp*> powerUps;
            
            bool applied;
        };
    }
}

#endif /* defined(__KillyCraft__PowerUpComponent__) */