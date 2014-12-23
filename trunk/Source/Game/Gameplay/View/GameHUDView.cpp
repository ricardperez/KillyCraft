//
//  GameHUDView.cpp
//  KillyCraft
//
//  Created by Ricard Perez del Campo on 02/12/14.
//  Copyright (c) 2014 MelonGames. All rights reserved.
//

#include "GameHUDView.h"
#include "Gameplay/Map.h"
#include "Gameplay/Player.h"
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
        , timeLabel(nullptr)
        , livesLabel(nullptr)
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
                
                timeLabel = cocos2d::Label::createWithTTF("", "Marker Felt.ttf", 25.0f);
                if (timeLabel)
                {
                    timeLabel->setColor(cocos2d::Color3B::GRAY);
                    timeLabel->setPosition(cocos2d::Vec2(10.0f, getContentSize().height - 10.0f));
                    timeLabel->setAnchorPoint(cocos2d::Vec2(0.0f, 1.0f));
                    addChild(timeLabel);
                    
                    schedule([this](float dt) -> void
                    {
                        timeLabel->setString(std::to_string(this->map->getElapsedTime()));
                    }, "update-time-label");
                }
                
                livesLabel = cocos2d::Label::createWithTTF("", "Marker Felt.ttf", 50.0f);
                if (livesLabel)
                {
                    livesLabel->setColor(cocos2d::Color3B::RED);
                    livesLabel->setPosition(cocos2d::Vec2(getContentSize().width - 10.0f, getContentSize().height - 10.0f));
                    livesLabel->setAnchorPoint(cocos2d::Vec2(1.0f, 1.0f));
                    addChild(livesLabel);
                }
                
                auto player = map->getPlayer();
                player->getLivesChangedSignal().Connect(Gallant::MakeDelegate(this, &GameHUDView::onPlayerLivesChanged));
                onPlayerLivesChanged(player);
                
                return true;
            }
            
            return false;
        }
        
        void GameHUDView::onPlayerLivesChanged(Player* player)
        {
            livesLabel->setString(std::to_string(player->getLives()));
        }
    }
}