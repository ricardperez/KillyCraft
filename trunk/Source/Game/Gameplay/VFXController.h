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
#include "View/FireWorks.h"

namespace cocos2d
{
    class Vec2;
    class ParticleSystemQuad;
    class LayerColor;
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
            void showFireWorks(int n);
            
            void showOpaqueLayer();
            void hideOpaqueLayer();
            
            bool isPlayingAnything() const;
            
        private:
            void updateParticleSystems(float dt);
            void updateFireWorks(float dt);
            
        private:
            Map* map;
            
            std::map<cocos2d::ParticleSystemQuad*, int> movingParticleSystems;
            std::vector<FireWorks> fireWorks;
            
            cocos2d::LayerColor* opaqueLayer;
        };
    }
}

#endif /* defined(__KillyCraft__VFXController__) */
