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
#include <map>

namespace cocos2d
{
    class Vec2;
    class ParticleSystemQuad;
}

namespace MelonGames
{
    namespace KillyCraft
    {
        class Map;
        class MapObject;
        class VFXController
        {
        public:
            VFXController(Map* map);
            void update(float dt);
            
            void showScoreNode(int score, const cocos2d::Vec2& position, bool moveUp);
            void showParticleSystem(const std::string& plistName, const cocos2d::Vec2& position);
            void showParticleSystem(const std::string& plistName, MapObject* object);
            
        private:
            Map* map;
            
            std::map<cocos2d::ParticleSystemQuad*, int> movingParticleSystems;
        };
    }
}

#endif /* defined(__KillyCraft__VFXController__) */
