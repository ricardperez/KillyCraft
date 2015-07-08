//
//  GameHUDView.h
//  KillyCraft
//
//  Created by Ricard Perez del Campo on 02/12/14.
//  Copyright (c) 2014 MelonGames. All rights reserved.
//

#ifndef __KillyCraft__GameHUDView__
#define __KillyCraft__GameHUDView__

#include "2d/CCNode.h"

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
        class WeaponComponent;
        
        class GameHUDView : public cocos2d::Node
        {
        public:
            static GameHUDView* create(const Map* map);
            
            virtual ~GameHUDView();
            
        private:
            GameHUDView();
            bool init(const Map* map);
            void update(float dt) override;
            
            void onPlayerLivesChanged(Player* player);
            void onPlayerWeaponComponentChanged(WeaponComponent* weaponComponent);
            
        private:
            const Map* map;
            
            cocos2d::Label* timeLabel;
            cocos2d::Label* livesLabel;
            cocos2d::Label* ammoLabel;
        };
    }
}

#endif /* defined(__KillyCraft__GameHUDView__) */
