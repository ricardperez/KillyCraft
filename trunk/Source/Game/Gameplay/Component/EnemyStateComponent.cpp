//
//  EnemyStateComponent.cpp
//  KillyCraft
//
//  Created by Ricard Perez del Campo on 23/12/14.
//  Copyright (c) 2014 MelonGames. All rights reserved.
//

#include "EnemyStateComponent.h"
#include "PositionComponent.h"
#include "Gameplay/MapObject.h"
#include "Gameplay/Map.h"
#include "Gameplay/MapEvents.h"
#include "Gameplay/VFXController.h"

namespace MelonGames
{
    namespace KillyCraft
    {
        EnemyStateComponent::EnemyStateComponent()
        : livesCost(0)
        , lives(0)
        , score(0)
        {
        }
        
        int EnemyStateComponent::getLivesCost() const
        {
            return livesCost;
        }
        
        int EnemyStateComponent::getLives() const
        {
            return lives;
        }
        
        int EnemyStateComponent::getScore() const
        {
            return score;
        }
        
        void EnemyStateComponent::removeLives(int nLives)
        {
            if (nLives >= lives)
            {
                lives = 0;
            }
            else
            {
                lives = (lives - nLives);
            }
            
            livesChangedSignal.Emit(this);
            
            if (lives <= 0)
            {
                if (!dieParticleSystems.empty())
                {
                    auto vfxController = object->getMap()->getVFXController();
                    const cocos2d::Vec2& position = object->get<PositionComponent>()->getPosition();
                    for (const auto& plist : dieParticleSystems)
                    {
                        vfxController->showParticleSystem(plist, position, true);
                    }
                }
                
                object->getMap()->getMapEvents()->getEnemyKilledSignal().Emit(object);
            }
        }
        
        Gallant::Signal1<EnemyStateComponent*>& EnemyStateComponent::getLivesChangedSignal()
        {
            return livesChangedSignal;
        }
    }
}