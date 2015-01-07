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
    class Label;
}

namespace MelonGames
{
    namespace KillyCraft
    {
        class Map;
        class Player;
        
        class GameHUDView : public cocos2d::Layer
        {
        public:
            static GameHUDView* create(const Map* map);
            
            virtual ~GameHUDView();
            
        private:
            GameHUDView();
            bool init(const Map* map);
            
            void onPlayerLivesChanged(Player* player);
            void onPlayerScoreChanged(Player* player);
            
        private:
            const Map* map;
            
            cocos2d::Label* timeLabel;
            cocos2d::Label* livesLabel;
            cocos2d::Label* scoreLabel;
        };
    }
}

#endif /* defined(__KillyCraft__GameHUDView__) */
