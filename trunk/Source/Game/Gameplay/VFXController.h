//
//  VFXController.h
//  KillyCraft
//
//  Created by Ricard Perez del Campo on 08/07/15.
//  Copyright (c) 2015 MelonGames. All rights reserved.
//

#ifndef __KillyCraft__VFXController__
#define __KillyCraft__VFXController__

#include <string>

namespace cocos2d
{
    class Vec2;
}

namespace MelonGames
{
    namespace KillyCraft
    {
        class Map;
        class VFXController
        {
        public:
            VFXController(Map* map);
            
            void showScoreNode(int score, const cocos2d::Vec2& position, bool moveUp);
            void showParticleSystem(const std::string& plistName, const cocos2d::Vec2& position);
            
        private:
            Map* map;
        };
    }
}

#endif /* defined(__KillyCraft__VFXController__) */
