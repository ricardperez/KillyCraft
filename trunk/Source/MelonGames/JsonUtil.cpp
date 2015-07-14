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
        void mergeContentToBase(const Json::Value& base, Json::Value& contentAndResult, MergeType mergeType)
        {
            if (base.isObject() && contentAndResult.isObject())
            {
                Json::Value::Members baseMembers = base.getMemberNames();
                for (const std::string& baseMember : baseMembers)
                {
                    if (contentAndResult.isMember(baseMember))
                    {
                        MergeType usedMergeType = mergeType;
                        if (usedMergeType == MergeType::eAutomatic)
                        {
                            usedMergeType = (MergeType)contentAndResult.get("merge", (int)mergeType).asInt();
                        }
                        
                        const Json::Value& baseValue = base[baseMember];
                        Json::Value& contentValue = contentAndResult[baseMember];
                        mergeContentToBase(baseValue, contentValue, usedMergeType);
                    }
                    else
                    {
                        contentAndResult[baseMember] = base[baseMember];
                    }
                }
            }
            else if (base.isArray() && contentAndResult.isArray())
            {
                switch (mergeType)
                {
                    case MergeType::eAll:
                        for (const auto& baseValue : base)
                        {
                            contentAndResult.append(baseValue);
                        }
                        break;
                    case MergeType::eBase:
                        contentAndResult = base;
                        break;
                    case MergeType::eOriginal:
                    case MergeType::eAutomatic:
                    default:
                        break;
                }
            }
        }
    }
}