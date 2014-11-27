//
//  MapGridView.h
//  KillyCraft
//
//  Created by Ricard Perez del Campo on 27/11/14.
//  Copyright (c) 2014 MelonGames. All rights reserved.
//

#ifndef __KillyCraft__MapGridView__
#define __KillyCraft__MapGridView__

#include "Game/GameConfig.h"

#ifdef DRAW_MAP_GRID

#include "2d/CCDrawNode.h"

namespace MelonGames
{
    namespace KillyCraft
    {
        class MapGridView : public cocos2d::DrawNode
        {
        public:
            static MapGridView* create();
            
        private:
            bool init();
        };
    }
    
}

#endif

#endif /* defined(__KillyCraft__MapGridView__) */
