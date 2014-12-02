//
//  GameHUDView.cpp
//  KillyCraft
//
//  Created by Ricard Perez del Campo on 02/12/14.
//  Copyright (c) 2014 MelonGames. All rights reserved.
//

#include "GameHUDView.h"
#include "Gameplay/Map.h"
#include "2d/CCLabel.h"

namespace MelonGames
{
    namespace KillyCraft
    {
        GameHUDView::~GameHUDView()
        {
        }
        
        GameHUDView::GameHUDView()
        : map(nullptr)
        {
        }
        
        GameHUDView* GameHUDView::create(const Map* map)
        {
            GameHUDView* result = new GameHUDView();
            if (result && result->init(map))
            {
                result->autorelease();
                return result;
            }
            
            delete result;
            return nullptr;
        }
        
        bool GameHUDView::init(const Map* map)
        {
            if (cocos2d::Layer::init())
            {
                this->map = map;
                
                if (auto timeLabel = cocos2d::Label::createWithTTF("", "Marker Felt.ttf", 25.0f))
                {
                    timeLabel->setColor(cocos2d::Color3B::GRAY);
                    timeLabel->setPosition(cocos2d::Vec2(10.0f, getContentSize().height - 10.0f));
                    timeLabel->setAnchorPoint(cocos2d::Vec2(0.0f, 1.0f));
                    addChild(timeLabel);
                    
                    schedule([timeLabel, this](float dt)->void{
                        timeLabel->setString(std::to_string(this->map->getElapsedTime()));
                    }, "update-time-label");
                }
                
                return true;
            }
            
            return false;
        }
    }
}