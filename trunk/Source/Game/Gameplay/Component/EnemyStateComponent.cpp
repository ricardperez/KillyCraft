//
//  EnemyStateComponent.cpp
//  KillyCraft
//
//  Created by Ricard Perez del Campo on 23/12/14.
//  Copyright (c) 2014 MelonGames. All rights reserved.
//

#include "EnemyStateComponent.h"

namespace MelonGames
{
    namespace KillyCraft
    {
        EnemyStateComponent::EnemyStateComponent()
        : livesCost(0)
        {
        }
        
        unsigned int EnemyStateComponent::getLivesCost() const
        {
            return livesCost;
        }
        
        void EnemyStateComponent::setLivesCost(unsigned int cost)
        {
            livesCost = cost;
        }
    }
}