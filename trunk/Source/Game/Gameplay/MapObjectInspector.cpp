//
//  MapObjectInspector.cpp
//  KillyCraft
//
//  Created by Ricard Perez del Campo on 23/12/14.
//  Copyright (c) 2014 MelonGames. All rights reserved.
//

#include "MapObjectInspector.h"
#include "Gameplay/MapObject.h"
#include "Gameplay/Component/EnemyStateComponent.h"

namespace MelonGames
{
    namespace KillyCraft
    {
        namespace MapObjectInspector
        {
            bool isEnemy(const MapObject* object)
            {
                return object->has<EnemyStateComponent>();
            }
        }
    }
}