//
//  JsonUtil.cpp
//  KillyCraft
//
//  Created by Ricard Perez del Campo on 10/01/15.
//  Copyright (c) 2015 MelonGames. All rights reserved.
//

#include "JsonUtil.h"

namespace MelonGames
{
    namespace JsonUtil
    {
        void mergeContentToBase(const Json::Value& base, Json::Value& contentAndResult)
        {
            if (base.isObject() && contentAndResult.isObject())
            {
                Json::Value::Members baseMembers = base.getMemberNames();
                for (const std::string& baseMember : baseMembers)
                {
                    if (contentAndResult.isMember(baseMember))
                    {
                        const Json::Value& baseValue = base[baseMember];
                        Json::Value& contentValue = contentAndResult[baseMember];
                        if (baseValue.isObject() && contentValue.isObject())
                        {
                            mergeContentToBase(baseValue, contentValue);
                        }
                    }
                    else
                    {
                        contentAndResult[baseMember] = base[baseMember];
                    }
                }
            }
        }
    }
}