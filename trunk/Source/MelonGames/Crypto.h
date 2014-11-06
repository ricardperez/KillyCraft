//
//  Crypto.h
//  KillyCraft
//
//  Created by Ricard Perez del Campo on 06/11/14.
//  Copyright (c) 2014 MelonGames. All rights reserved.
//

#ifndef __KillyCraft__Crypto__
#define __KillyCraft__Crypto__

#include <string>

namespace MelonGames
{
    namespace Crypto
    {
        unsigned int stringHash(const std::string& str, int seed = 0);
    }
}

#endif /* defined(__KillyCraft__Crypto__) */
