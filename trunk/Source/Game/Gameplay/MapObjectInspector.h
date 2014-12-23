//
//  MapObjectInspector.h
//  KillyCraft
//
//  Created by Ricard Perez del Campo on 23/12/14.
//  Copyright (c) 2014 MelonGames. All rights reserved.
//

#ifndef __KillyCraft__MapObjectInspector__
#define __KillyCraft__MapObjectInspector__

namespace MelonGames
{
    namespace KillyCraft
    {
        class MapObject;
        
        namespace MapObjectInspector
        {
            bool isEnemy(const MapObject* object);
            bool isPlayer(const MapObject* object);
        }
    }
}

#endif /* defined(__KillyCraft__MapObjectInspector__) */
