//
//  BehaviourComponent.cpp
//  KillyCraft
//
//  Created by Ricard Perez del Campo on 31/10/14.
//  Copyright (c) 2014 MelonGames. All rights reserved.
//

#include "BehaviourComponent.h"

namespace MelonGames
{
    namespace KillyCraft
    {
        void BehaviourComponent::update(float dt)
        {
            Base::update(dt);
            for (auto behaviour : behaviours)
            {
                behaviour->update(object, dt);
            }
        }
        
        void BehaviourComponent::addBehaviour(Behaviour *b)
        {
            behaviours.push_back(b);
        }
    }
}