//
//  ShieldComponent.cpp
//  KillyCraft
//
//  Created by Ricard Perez del Campo on 06/08/15.
//  Copyright (c) 2015 MelonGames. All rights reserved.
//

#include "ShieldComponent.h"
#include "Gameplay/MapObject.h"
#include "EnemyStateComponent.h"
#include "ViewComponent.h"
#include "ViewParts.h"
#include "2d/CCNode.h"
#include "2d/CCActionInterval.h"

namespace MelonGames
{
    namespace KillyCraft
    {
        ShieldComponent::ShieldComponent()
        : spritePart(nullptr)
        {
            
        }
        
        void ShieldComponent::onObjectAttachedToMap()
        {
            Base::onObjectAttachedToMap();
            
            if (auto enemyState = object->get<EnemyStateComponent>())
            {
                enemyState->getLivesChangedSignal().Connect(this, &ShieldComponent::onEnemyLivesChanged);
            }
        }
        
        void ShieldComponent::onWillDetachFromObject()
        {
            if (spritePart)
            {
                auto viewComponent = object->get<ViewComponent>();
                viewComponent->removePart(spritePart);
                delete spritePart;
                spritePart = nullptr;
            }
            
            Base::onWillDetachFromObject();
        }
        
        void ShieldComponent::onEnemyLivesChanged(EnemyStateComponent* enemyStateComponent)
        {
            if (!spritePart)
            {
                spritePart = new ViewPartSprite(assetName);
                object->get<ViewComponent>()->addPart(spritePart, false);
                spritePart->getNode()->setOpacity(0);
            }
            
            const int kTag = 8874;
            spritePart->getNode()->stopActionByTag(kTag);
            spritePart->getNode()->runAction(cocos2d::Sequence::create(cocos2d::FadeTo::create(0.1f, 128),
                                                                       cocos2d::DelayTime::create(0.5f),
                                                                       cocos2d::FadeTo::create(0.1f, 0),
                                                                       nullptr))->setTag(kTag);
        }
    }
}