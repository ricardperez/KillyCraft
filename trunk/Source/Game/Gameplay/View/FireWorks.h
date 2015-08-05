//
//  FireWorks.h
//  KillyCraft
//
//  Created by Ricard Perez del Campo on 04/08/15.
//  Copyright (c) 2015 MelonGames. All rights reserved.
//

#ifndef __KillyCraft__FireWorks__
#define __KillyCraft__FireWorks__

#include <string>
#include "math/Vec2.h"
#include "base/ccTypes.h"

namespace cocos2d
{
    class Node;
    class ParticleSystemQuad;
}

namespace MelonGames
{
    namespace KillyCraft
    {
        class FireWorks
        {
        public:
            struct Definition
            {
                std::string rocketParticleSystemName;
                std::string explosionParticleSystemName;
                
                cocos2d::Vec2 rocketStartPosition;
                cocos2d::Vec2 rocketSpeed;
                
                float startDelay;
                float rocketTime;
                
                cocos2d::Color4F explosionStartColor;
                cocos2d::Color4F explosionStartColorVar;
                cocos2d::Color4F explosionEndColor;
                cocos2d::Color4F explosionEndColorVar;
                
                cocos2d::Node* parentNode;
            };
            
            FireWorks(const FireWorks::Definition& definition);
            
            void update(float dt);
            
            bool isDone() const;
            void release();
            
        private:
            FireWorks::Definition definition;
            float time;
            
            cocos2d::Vec2 rocketPosition;
            
            cocos2d::ParticleSystemQuad* rocketParticleSystem;
            cocos2d::ParticleSystemQuad* explosionParticleSystem;
        };
    }
}

#endif /* defined(__KillyCraft__FireWorks__) */
