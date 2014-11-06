//
//  Crypto.cpp
//  KillyCraft
//
//  Created by Ricard Perez del Campo on 06/11/14.
//  Copyright (c) 2014 MelonGames. All rights reserved.
//

#include "Crypto.h"

namespace MelonGames
{
    namespace Crypto
    {
        unsigned int stringHash(const std::string& str, int seed)
        {
            unsigned int result = seed;
            
            const char* s = str.c_str();
            while (*s)
            {
                result = result * 101  +  *s++;
            }
            
            return result;
        }
    }
}