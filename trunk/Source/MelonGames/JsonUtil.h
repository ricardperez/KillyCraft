//
//  JsonUtil.h
//  KillyCraft
//
//  Created by Ricard Perez del Campo on 10/01/15.
//  Copyright (c) 2015 MelonGames. All rights reserved.
//

#ifndef __KillyCraft__JsonUtil__
#define __KillyCraft__JsonUtil__

#include "json/json.h"

namespace MelonGames
{
    namespace JsonUtil
    {
        enum class MergeType
        {
            eAutomatic = 0,
            eOriginal = 1,
            eBase = 2,
            eAll = 3,
        };
        
        void mergeContentToBase(const Json::Value& base, Json::Value& contentAndResult, MergeType mergeType);
    }
}

#endif /* defined(__KillyCraft__JsonUtil__) */
