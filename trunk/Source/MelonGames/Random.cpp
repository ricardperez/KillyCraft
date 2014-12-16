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
        dis = std::uniform_int_distribution<>(getMin(), getMax());
    }
    
    Random& Random::getInstance()
    {
        static Random instance;
        return instance;
    }
    
    float Random::next()
    {
        return (((float)dis(gen)) / getMax());
    }
    
    int Random::getMax() const
    {
        return std::numeric_limits<int>::max();
    }
    
    int Random::getMin() const
    {
        return 0;
    }
    
    int Random::nextIntInRange(int min, int max, bool minInclusive, bool maxInclusive)
    {
        int rnd = dis(gen);
        
        int m = (minInclusive ? min : min+1);
        int M = (maxInclusive ? max : max-1);
        
        return (m + rnd % (M - m + 1));
    }
}