//
//  PlayerStateComponent.h
//  KillyCraft
//
//  Created by Ricard Perez del Campo on 06/08/15.
//  Copyright (c) 2015 MelonGames. All rights reserved.
//

#ifndef __KillyCraft__PlayerStateComponent__
#define __KillyCraft__PlayerStateComponent__

#include "Component.h"

namespace MelonGames
{
    namespace KillyCraft
    {
        namespace ComponentsFactory
        {
            Component* createPlayerStateComponent(const Json::Value& json);
        }
        
        class CollisionDetectionComponent;
        
        class PlayerStateComponent : public Component
        {
        public:
            DECLARE_TYPE_WITH_BASE_TYPE(PlayerStateComponent, Component);
            
            friend Component* ComponentsFactory::createPlayerStateComponent(const Json::Value& json);
            
            virtual void onObjectAttachedToMap() override;
            virtual void onWillDetachFromObject() override;
            
        private:
            void onPlayerCollision(CollisionDetectionComponent* playerCollisionDetection, CollisionDetectionComponent* otherCollisionDetection);
            void onEnemyKilled(MapObject* enemy);
        };
    }
}

#endif /* defined(__KillyCraft__PlayerStateComponent__) */
