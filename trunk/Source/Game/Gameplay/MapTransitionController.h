//
//  MapTransitionController.h
//  KillyCraft
//
//  Created by Ricard Perez del Campo on 17/02/15.
//  Copyright (c) 2015 MelonGames. All rights reserved.
//

#ifndef __KillyCraft__MapTransitionController__
#define __KillyCraft__MapTransitionController__

#include "Signal/Signal.h"

namespace MelonGames
{
    namespace KillyCraft
    {
        class Map;
        class MapObject;
        
        class MapTransitionController
        {
        public:
            MapTransitionController(Map* map);
            
            void startTransition();
            bool isTransitioning() const;
            void update(float dt);
            
            Gallant::Signal1<MapTransitionController*>& getTransitionFinishedSignal();
            
        private:
            void checkState();
            
        private:
            Gallant::Signal1<MapTransitionController*> transitionFinishedSignal;
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
