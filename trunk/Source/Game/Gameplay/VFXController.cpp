//
//  VFXController.cpp
//  KillyCraft
//
//  Created by Ricard Perez del Campo on 08/07/15.
//  Copyright (c) 2015 MelonGames. All rights reserved.
//

#include "VFXController.h"
#include "Map.h"
#include "View/MapView.h"
#include "Random.h"
#include "2d/CCLabel.h"
#include "2d/CCActionInterval.h"
#include "2d/CCActionInstant.h"

namespace MelonGames
{
    namespace KillyCraft
    {
        VFXController::VFXController(Map* map)
        : map(map)
        {
            
        }
        
        void VFXController::showScoreNode(int score, const cocos2d::Vec2& position, bool moveUp)
        {
            auto label = cocos2d::Label::createWithTTF(std::to_string(score), "Marker Felt.ttf", 25.0f);
            label->setColor(cocos2d::Color3B::WHITE);
            label->setPosition(position);
            label->setAnchorPoint(cocos2d::Vec2(0.0f, 1.0f));
            map->getView()->getNode()->addChild(label);
            
            cocos2d::Vec2 offset;
            if (moveUp)
            {
                offset.x = Random::getInstance().nextRealInRange(-10.0f, 10.0f);
                offset.y = Random::getInstance().nextRealInRange(65.0f, 100.0f);
            }
            
            label->runAction(cocos2d::Sequence::create(cocos2d::Spawn::create(cocos2d::MoveBy::create(1.0f, offset),
                                                                              cocos2d::FadeOut::create(1.0f),
                                                                              nullptr),
                                                       cocos2d::RemoveSelf::create(),
                                                       nullptr));
        }
        
        void VFXController::showParticleSystem(const std::string& plistName, const cocos2d::Vec2& position)
        {
            
        }
    }
}