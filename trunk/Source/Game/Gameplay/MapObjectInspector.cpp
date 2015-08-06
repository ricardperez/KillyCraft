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
#include "Gameplay/Component/PlayerStateComponent.h"
#include "Gameplay/Component/ProjectileStateComponent.h"
#include "Gameplay/Component/PowerUpComponent.h"

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
            
            bool isPlayer(const MapObject* object)
            {
                return object->has<PlayerStateComponent>();
            }
            
            bool isProjectile(const MapObject* object)
            {
                return object->has<ProjectileStateComponent>();
            }
            
            bool isPowerUp(const MapObject* object)
            {
                return object->has<PowerUpComponent>();
            }
        }
    }
}