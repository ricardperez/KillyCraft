//
//  MoveActions.h
//  KillyCraft
//
//  Created by Ricard Perez del Campo on 20/01/15.
//  Copyright (c) 2015 MelonGames. All rights reserved.
//

#ifndef __KillyCraft__MoveActions__
#define __KillyCraft__MoveActions__

namespace cocos2d
{
    class Vec3;
}

namespace MelonGames
{
    namespace KillyCraft
    {
        class MapObject;
        
        namespace MoveActions
        {
            void moveByVector(MapObject* object, const cocos2d::Vec3& vector);
            void moveByVector(MapObject* object, float x, float y, float z);
            void moveByVector(MapObject* object, float x, float y);
            void moveOnX(MapObject* object, float x);
            void moveOnY(MapObject* object, float y);
        }
    }
}

#endif /* defined(__KillyCraft__MoveActions__) */
