//
//  MapTransitionController.cpp
//  KillyCraft
//
//  Created by Ricard Perez del Campo on 17/02/15.
//  Copyright (c) 2015 MelonGames. All rights reserved.
//

#include "MapTransitionController.h"
#include "Map.h"
#include "MapObject.h"
#include "MapObjectInspector.h"
#include "MapObjectsFactory.h"
#include "Component/BehaviourComponent.h"
#include "Component/MovementStateComponents.h"
#include "Component/PositionComponent.h"
#include "Component/ViewComponent.h"
#include "Behaviour/MovementBehaviours.h"

namespace MelonGames
{
    namespace KillyCraft
    {
        MapTransitionController::MapTransitionController(Gallant::Delegate1<MapTransitionController*> handler, Map* map)
        : handler(handler)
        , map(map)
        , mapPlayer(nullptr)
        , mapTransitionPlayer(nullptr)
        , state(State::eNone)
        {
            
        }
        
        void MapTransitionController::startTransition()
        {
            CCASSERT(state == State::eNone, "Calling MapTransitionController::startTransition() with a state different than eNone");
            state = State::eStart;
        }
        
        bool MapTransitionController::isTransitioning() const
        {
            return ((state != State::eNone) && (state != State::eFinished));
        }
        
        void MapTransitionController::update(float dt)
        {
            switch (state)
            {
                case State::eNone:
                default:
                    break;
                case State::eStart:
                {
                    if (!map->isAnyObjectPassingFilter(MapObjectInspector::isEnemy))
                    {
                        mapPlayer = map->getObjectPassingFilter(MapObjectInspector::isPlayer);
                        CCASSERT(mapPlayer != nullptr, "There must be a player object at this point");
                        if (mapPlayer)
                        {
                            mapTransitionPlayer = map->getFactory()->createObject("PlayerTransition");
                            CCASSERT(mapTransitionPlayer != nullptr, "A PlayerTransition template must exist");
                            if (mapTransitionPlayer)
                            {
                                map->addObject(mapTransitionPlayer);
                                mapTransitionPlayer->get<PositionComponent>()->setPosition(mapPlayer->get<PositionComponent>()->getPosition());
                                mapPlayer->get<ViewComponent>()->setVisible(false);
                                
                                auto movementComponent = mapTransitionPlayer->getOrCreate<MoveLinearStateComponent>();
                                movementComponent->setMovementPerSecond(cocos2d::Vec3(0.0f, 500.0f, 0.0f));
                                state = State::eMovingIn;
                            }
                            else
                            {
                                state = State::eFinished;
                            }
                        }
                        else
                        {
                            state = State::eFinished;
                        }
                    }
                    break;
                }
                case State::eMovingIn:
                {
                    auto posComponent = mapTransitionPlayer->get<PositionComponent>();
                    if (posComponent->getPosition().y >= 400.0f)
                    {
                        auto movementComponent = mapTransitionPlayer->get<MoveLinearStateComponent>();
                        movementComponent->setMovementPerSecond(cocos2d::Vec3(0.0f, 0.0f, 0.0f));
                        state = State::eWaitingIn;
                    }
                    break;
                }
                case State::eWaitingIn:
                {
                    auto movementComponent = mapTransitionPlayer->get<MoveLinearStateComponent>();
                    movementComponent->setMovementPerSecond(cocos2d::Vec3(0.0f, -500.0f, 0.0f));
                    state = State::eMovingOut;
                    break;
                }
                case State::eMovingOut:
                {
                    auto posComponent = mapTransitionPlayer->get<PositionComponent>();
                    if (posComponent->getPosition().y <= mapPlayer->get<PositionComponent>()->getPosition().y)
                    {
                        auto movementComponent = mapTransitionPlayer->get<MoveLinearStateComponent>();
                        movementComponent->setMovementPerSecond(cocos2d::Vec3(0.0f, 0.0f, 0.0f));
                        state = State::eWaitingOut;
                    }
                    break;
                }
                case State::eWaitingOut:
                {
                    state = State::eFinished;
                    break;
                }
                case State::eFinished:
                {
                    mapPlayer->get<ViewComponent>()->setVisible(true);
                    mapPlayer->get<PositionComponent>()->setPosition(mapTransitionPlayer->get<PositionComponent>()->getPosition());
                    mapTransitionPlayer->get<ViewComponent>()->setVisible(false);
                    map->removeObjectWhenPossible(mapTransitionPlayer);
                    mapTransitionPlayer = nullptr;
                    state = State::eNone;
                    handler(this);
                    break;
                }
            }
        }
    }
}
