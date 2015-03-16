//
//  MapTransitionController.h
//  KillyCraft
//
//  Created by Ricard Perez del Campo on 17/02/15.
//  Copyright (c) 2015 MelonGames. All rights reserved.
//

#ifndef __KillyCraft__MapTransitionController__
#define __KillyCraft__MapTransitionController__

I was here making this guy be the responsible for moving tha player object after some squads have been spawned instead of the map itself...

namespace MelonGames
{
    namespace KillyCraft
    {
        class MapTransitionController
        {
        public:
            MapTransitionController();
            
            void startTransition();
            bool isTransitioning();
            
        private:
            Gallant::Signal1<MapTransitionController*> transitionFinishedSignal;
        };
    }
}

#endif /* defined(__KillyCraft__MapTransitionController__) */
