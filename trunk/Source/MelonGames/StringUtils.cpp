//
//  StringUtils.cpp
//  KillyCraft
//
//  Created by Ricard Perez del Campo on 04/08/15.
//  Copyright (c) 2015 MelonGames. All rights reserved.
//

#include "StringUtils.h"
#include <sstream>

namespace MelonGames
{
    std::vector<std::string> StringUtils::split(const std::string& string, const std::string& delimiter)
    {
        std::vector<std::string> result;
        
        std::string::size_type start = 0;
        std::string::size_type end = string.find(delimiter, start);
        
        bool skip = (end == start);
        
        while (end != std::string::npos)
        {
            if (!skip)
            {
                std::string part = string.substr(start, end-start);
                result.push_back(part);
            }
            
            start = end + delimiter.size();
            end = string.find(delimiter, start);
            
            skip = (start == end);
        }
        
        if (start != string.size())
        {
            std::string lastPart = string.substr(start, string.size() - start);
            result.push_back(lastPart);
        }
        
        return result;
    }
    
    std::string StringUtils::join(const std::vector<std::string>& parts, const std::string& delimiter)
    {
        std::string result;
        
        size_t i = 0;
        for (const auto& part : parts)
        {
            result += part;
            if (i != parts.size()-1)
            {
                result += delimiter;
            }
            ++i;
        }
        
        return result;
    }
}