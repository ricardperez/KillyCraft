//
//  FireWorks.cpp
//  KillyCraft
//
//  Created by Ricard Perez del Campo on 04/08/15.
//  Copyright (c) 2015 MelonGames. All rights reserved.
//

#include "FireWorks.h"
#include "2d/CCParticleSystemQuad.h"

namespace MelonGames
{
    namespace KillyCraft
    {
        FireWorks::FireWorks(const FireWorks::Definition& definition)
        : definition(definition)
        , time(0.0f)
        , rocketParticleSystem(nullptr)
        , explosionParticleSystem(nullptr)
        {
            rocketPosition = definition.rocketStartPosition;
        }
        
        void FireWorks::update(float dt)
        {
            time += dt;
            
            if (time < definition.startDelay)
            {
                return;
            }
            
            if (time < (definition.startDelay + definition.rocketTime))
            {
                if (!rocketParticleSystem)
                {
                    rocketParticleSystem = cocos2d::ParticleSystemQuad::create(definition.rocketParticleSystemName);
                    definition.parentNode->addChild(rocketParticleSystem);
                    rocketParticleSystem->setRotation(-CC_RADIANS_TO_DEGREES(definition.rocketSpeed.getAngle()));
                }
                rocketPosition += (definition.rocketSpeed * dt);
                rocketParticleSystem->setPosition(rocketPosition);
            }
            else
            {
                if (rocketParticleSystem)
                {
                    rocketParticleSystem->removeFromParent();
                    rocketParticleSystem = nullptr;
                }
                
                if (!explosionParticleSystem)
                {
                    explosionParticleSystem = cocos2d::ParticleSystemQuad::create(definition.explosionParticleSystemName);
                    explosionParticleSystem->setStartColor(definition.explosionStartColor);
                    explosionParticleSystem->setStartColorVar(definition.explosionStartColorVar);
                    explosionParticleSystem->setEndColor(definition.explosionEndColor);
                    explosionParticleSystem->setEndColorVar(definition.explosionEndColorVar);
                    explosionParticleSystem->setAutoRemoveOnFinish(true);
                    explosionParticleSystem->retain();
                    explosionParticleSystem->setPosition(rocketPosition);
                    definition.parentNode->addChild(explosionParticleSystem);
                }
            }
        }
        
        bool FireWorks::isDone() const
        {
            return (explosionParticleSystem && (explosionParticleSystem->getParent() == nullptr));
        }
        
        void FireWorks::release()
        {
            if (explosionParticleSystem)
            {
                explosionParticleSystem->removeFromParent();
                explosionParticleSystem->release();
                explosionParticleSystem = nullptr;
            }
        }
    }
}