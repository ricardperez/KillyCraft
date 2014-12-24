//
//  ComponentsFactory.h
//  KillyCraft
//
//  Created by Ricard Perez del Campo on 24/12/14.
//  Copyright (c) 2014 MelonGames. All rights reserved.
//

#ifndef __KillyCraft__ComponentsFactory__
#define __KillyCraft__ComponentsFactory__

namespace Json
{
    class Value;
}

namespace MelonGames
{
    namespace KillyCraft
    {
        class Component;
        
        namespace ComponentsFactory
        {
            Component* createComponent(const Json::Value& json);
        }
    }
}

#endif /* defined(__KillyCraft__ComponentsFactory__) */
