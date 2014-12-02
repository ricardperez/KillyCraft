//
//  GameHUDView.h
//  KillyCraft
//
//  Created by Ricard Perez del Campo on 02/12/14.
//  Copyright (c) 2014 MelonGames. All rights reserved.
//

#ifndef __KillyCraft__GameHUDView__
#define __KillyCraft__GameHUDView__

#include "2d/CCLayer.h"

namespace cocos2d
{
    class LabelAtlas;
}

namespace MelonGames
{
    namespace KillyCraft
    {
        class Map;
        
        class GameHUDView : public cocos2d::Layer
        {
        public:
            static GameHUDView* create(const Map* map);
            
            virtual ~GameHUDView();
            
        private:
            GameHUDView();
            bool init(const Map* map);
            
        private:
            const Map* map;
        };
    }
}

#endif /* defined(__KillyCraft__GameHUDView__) */
