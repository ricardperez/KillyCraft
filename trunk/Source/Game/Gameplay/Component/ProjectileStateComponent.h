//
//  ProjectileStateComponent.h
//  KillyCraft
//
//  Created by Ricard Perez del Campo on 24/12/14.
//  Copyright (c) 2014 MelonGames. All rights reserved.
//

#ifndef __KillyCraft__ProjectileStateComponent__
#define __KillyCraft__ProjectileStateComponent__

#include "Component.h"

namespace MelonGames
{
    namespace KillyCraft
    {
        namespace ComponentsFactory
        {
            Component* createProjectileStateComponent(const Json::Value& json);
        }
        
        class CollisionDetectionComponent;
        
        class ProjectileStateComponent : public Component
        {
            friend Component* ComponentsFactory::createProjectileStateComponent(const Json::Value& json);
            
        public:
            DECLARE_TYPE_WITH_BASE_TYPE(ProjectileStateComponent, Component);
            
            ProjectileStateComponent();
            
            virtual void onObjectAttachedToMap() override;
            virtual void onWillDetachFromObject() override;
            
            unsigned int getPower() const;
            
        private:
            void onCollision(CollisionDetectionComponent* first, CollisionDetectionComponent* second);
            
        private:
            unsigned int power;
            unsigned int nCollisionsSupported;
            unsigned int nCollisionsHappened;
        };
    }
}

#endif /* defined(__KillyCraft__ProjectileStateComponent__) */
