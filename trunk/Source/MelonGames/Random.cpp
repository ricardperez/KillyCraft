//
//  Random.cpp
//  KillyCraft
//
//  Created by Ricard Perez del Campo on 06/11/14.
//  Copyright (c) 2014 MelonGames. All rights reserved.
//

#include "Random.h"

namespace MelonGames
{
    Random::Random()
    {
        gen = std::mt19937(rd());
        dis = std::uniform_real_distribution<>(0, 1);
    }
    
    Random& Random::getInstance()
    {
        static Random instance;
        return instance;
    }
    
    float Random::next()
    {
        return dis(gen);
    }
}