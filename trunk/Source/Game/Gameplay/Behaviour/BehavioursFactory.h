//
//  BehavioursFactory.h
//  KillyCraft
//
//  Created by Ricard Perez del Campo on 24/12/14.
//  Copyright (c) 2014 MelonGames. All rights reserved.
//

#ifndef KillyCraft_BehavioursFactory_h
#define KillyCraft_BehavioursFactory_h

namespace Json
{
    class Value;
}

namespace MelonGames
{
    namespace KillyCraft
    {
        class Behaviour;
        
        namespace BehavioursFactory
        {
            Behaviour* createBehaviour(const Json::Value& json);
        }
    }
}

#endif
