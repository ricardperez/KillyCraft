//
//  MovementBehaviours.h
//  KillyCraft
//
//  Created by Ricard Perez del Campo on 31/10/14.
//  Copyright (c) 2014 MelonGames. All rights reserved.
//

#ifndef __KillyCraft__MovementBehaviours__
#define __KillyCraft__MovementBehaviours__

#include "Behaviour.h"

namespace MelonGames
{
    namespace KillyCraft
    {
        class MoveWithBackgroundBehaviour : public Behaviour
        {
        public:
            DECLARE_TYPE_WITH_BASE_TYPE(MoveWithBackgroundBehaviour, Behaviour);
            
            void update(MapObject* object, float dt) override;
        };
        
        class MoveLinearBehaviour : public Behaviour
        {
        public:
            DECLARE_TYPE_WITH_BASE_TYPE(MoveLinearBehaviour, Behaviour);
            
            MoveLinearBehaviour();
            enum class Projection
            {
                eNormal,
                eVertical,
                eHorizontal
            };
            
            void setProjection(Projection projection);
            
            virtual void update(MapObject* object, float dt) override;
            
        private:
            Projection projection;
        };
        
        class MoveCircularBehaviour : public Behaviour
        {
        public:
            DECLARE_TYPE_WITH_BASE_TYPE(MoveCircularBehaviour, Behaviour);
            
            virtual void update(MapObject* object, float dt) override;
        };
        
        class MoveCircularProjectedBehaviour : public Behaviour
        {
        public:
            DECLARE_TYPE_WITH_BASE_TYPE(MoveCircularProjectedBehaviour, Behaviour);
            
            virtual void update(MapObject* object, float dt) override;
        };
    }
}

#endif /* defined(__KillyCraft__MovementBehaviours__) */
