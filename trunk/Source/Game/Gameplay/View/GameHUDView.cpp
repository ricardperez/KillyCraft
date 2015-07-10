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
#include "Gameplay/MapObject.h"
#include "Gameplay/Component/WeaponComponent.h"
#include "MelonGames/SpriteFrameHelper.h"
#include "2d/CCLabel.h"
#include "ui/UIScale9Sprite.h"
#include "base/CCDirector.h"

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
        , ammoLabel(nullptr)
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
            if (cocos2d::Node::init())
            {
                const cocos2d::Size size(cocos2d::Director::getInstance()->getWinSize().width, 65.0f);
                setContentSize(size);
                
                this->map = map;
                
                auto background = cocos2d::ui::Scale9Sprite::createWithSpriteFrame(spriteFrameOrDefault("black_gradient.png"));
                background->setContentSize(size);
                background->setAnchorPoint(cocos2d::Vec2::ZERO);
                background->setOpacity(120);
                addChild(background);
                
                livesLabel = cocos2d::Label::createWithTTF("", "Marker Felt.ttf", 25.0f);
                livesLabel->setColor(cocos2d::Color3B::RED);
                livesLabel->setPosition(cocos2d::Vec2(10.0f, getContentSize().height - 5.0f));
                livesLabel->setAnchorPoint(cocos2d::Vec2(0.0f, 1.0f));
                addChild(livesLabel);
                
                ammoLabel = cocos2d::Label::createWithTTF("", "Marker Felt.ttf", 25.0f);
                ammoLabel->setPosition(cocos2d::Vec2(10.0f, 5.0f));
                ammoLabel->setAnchorPoint(cocos2d::Vec2(0.0f, 0.0f));
                addChild(ammoLabel);
                
                timeLabel = cocos2d::Label::createWithTTF("", "Marker Felt.ttf", 25.0f);
                timeLabel->setColor(cocos2d::Color3B::GRAY);
                timeLabel->setPosition(cocos2d::Vec2(getContentSize().width - 10.0f, 5.0f));
                timeLabel->setAnchorPoint(cocos2d::Vec2(1.0f, 0.0f));
                addChild(timeLabel);
                
                auto player = map->getPlayer();
                
                player->getLivesChangedSignal().Connect(this, &GameHUDView::onPlayerLivesChanged);
                onPlayerLivesChanged(player);
                
                auto weaponComponent = player->getPlayerObject()->get<WeaponComponent>();
                weaponComponent->getChangedSignal().Connect(this, &GameHUDView::onPlayerWeaponComponentChanged);
                onPlayerWeaponComponentChanged(weaponComponent);
                
                scheduleUpdate();
                
                return true;
            }
            
            return false;
        }
        
        void GameHUDView::update(float dt)
        {
            static char timerString[10];
            sprintf(timerString, "%.2f", map->getElapsedTime());
            timeLabel->setString(timerString);
        }
        
        void GameHUDView::onPlayerLivesChanged(Player* player)
        {
            livesLabel->setString("Lives: " + std::to_string(player->getLives()));
        }
        
        void GameHUDView::onPlayerWeaponComponentChanged(WeaponComponent* weaponComponent)
        {
            ammoLabel->setString("Ammo: " + std::to_string(weaponComponent->getNBullets()));
        }
    }
}