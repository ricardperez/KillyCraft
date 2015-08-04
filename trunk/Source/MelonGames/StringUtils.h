//
//  StringUtils.h
//  KillyCraft
//
//  Created by Ricard Perez del Campo on 04/08/15.
//  Copyright (c) 2015 MelonGames. All rights reserved.
//

#ifndef __KillyCraft__StringUtils__
#define __KillyCraft__StringUtils__

#include <string>
#include <vector>

namespace MelonGames
{
    class StringUtils
    {
    public:
        static std::vector<std::string> split(const std::string& string, const std::string& delimiter);
        static std::string join(const std::vector<std::string>& parts, const std::string& delimiter);
    };
}

#endif /* defined(__KillyCraft__StringUtils__) */
