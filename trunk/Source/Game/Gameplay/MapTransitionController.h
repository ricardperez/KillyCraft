//
//  MapTransitionController.h
//  KillyCraft
//
//  Created by Ricard Perez del Campo on 17/02/15.
//  Copyright (c) 2015 MelonGames. All rights reserved.
//

#ifndef __KillyCraft__MapTransitionController__
#define __KillyCraft__MapTransitionController__

#include "Signal/Delegate.h"

namespace MelonGames
{
    namespace KillyCraft
    {
        class Map;
        class MapObject;
        
        class MapTransitionController
        {
        public:
            MapTransitionController(Gallant::Delegate1<MapTransitionController*> handler, Map* map);
            
            void startTransition();
            bool isTransitioning() const;
            void update(float dt);
            
        private:
            void checkState();
            
        private:
            const Gallant::Delegate1<MapTransitionController*> handler;
            Map* map;
            MapObject* mapPlayer;
            MapObject* mapTransitionPlayer;
            
            float stateTime;
            
            enum class State
            {
                eNone,
                eStart,
                eMovingIn,
                eWaitingIn,
                eMovingOut,
                eWaitingOut,
                eFinished
            } state;
        };
    }
}

#endif /* defined(__KillyCraft__MapTransitionController__) */
