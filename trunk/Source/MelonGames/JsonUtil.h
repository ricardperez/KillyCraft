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
        void mergeContentToBase(const Json::Value& base, Json::Value& contentAndResult);
    }
}

#endif /* defined(__KillyCraft__JsonUtil__) */
