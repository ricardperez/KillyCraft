//
//  EnemyStateComponent.h
//  KillyCraft
//
//  Created by Ricard Perez del Campo on 23/12/14.
//  Copyright (c) 2014 MelonGames. All rights reserved.
//

#ifndef __KillyCraft__EnemyStateComponent__
#define __KillyCraft__EnemyStateComponent__

#include "Component.h"
#include "Signal/Signal.h"
#include <vector>

namespace MelonGames
{
    namespace KillyCraft
    {
        namespace ComponentsFactory
        {
            Component* createEnemyStateComponent(const Json::Value& json);
        }
        
        class EnemyStateComponent : public Component
        {
        public:
            DECLARE_TYPE_WITH_BASE_TYPE(EnemyStateComponent, Component);
            
            friend Component* ComponentsFactory::createEnemyStateComponent(const Json::Value& json);
            
            EnemyStateComponent();
            
            int getLivesCost() const;
            int getLives() const;
            int getScore() const;
            
            void removeLives(int nLives);
            
            Gallant::Signal1<EnemyStateComponent*>& getLivesChangedSignal();
            
        private:
            int livesCost;
            int lives;
            int score;
            std::vector<std::string> dieParticleSystems;
            
            Gallant::Signal1<EnemyStateComponent*> livesChangedSignal;
        };
    }
}

#endif /* defined(__KillyCraft__EnemyStateComponent__) */
