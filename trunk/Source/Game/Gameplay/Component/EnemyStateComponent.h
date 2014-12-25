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
            
            friend class ObjectsFastFactory;
            friend Component* ComponentsFactory::createEnemyStateComponent(const Json::Value& json);
            
            EnemyStateComponent();
            
            unsigned int getLivesCost() const;
            unsigned int getLives() const;
            unsigned int getScore() const;
            
            void removeLives(unsigned int nLives);
            
        private:
            unsigned int livesCost;
            unsigned int lives;
            unsigned int score;
        };
    }
}

#endif /* defined(__KillyCraft__EnemyStateComponent__) */
