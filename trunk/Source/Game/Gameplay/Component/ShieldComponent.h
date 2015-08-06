//
//  ShieldComponent.h
//  KillyCraft
//
//  Created by Ricard Perez del Campo on 06/08/15.
//  Copyright (c) 2015 MelonGames. All rights reserved.
//

#ifndef __KillyCraft__ShieldComponent__
#define __KillyCraft__ShieldComponent__

#include "Component.h"

namespace MelonGames
{
    namespace KillyCraft
    {
        namespace ComponentsFactory
        {
            Component* createShieldComponent(const Json::Value& json);
        }
        
        class EnemyStateComponent;
        class ViewPartSprite;
        
        class ShieldComponent : public Component
        {
        public:
            DECLARE_TYPE_WITH_BASE_TYPE(ShieldComponent, Component);
            
            friend Component* ComponentsFactory::createShieldComponent(const Json::Value& json);
            
            ShieldComponent();
            
            void onObjectAttachedToMap() override;
            void onWillDetachFromObject() override;
            
        private:
            void onEnemyLivesChanged(EnemyStateComponent* enemyStateComponent);
            
        private:
            std::string assetName;
            ViewPartSprite* spritePart;
        };
    }
}

#endif /* defined(__KillyCraft__ShieldComponent__) */
