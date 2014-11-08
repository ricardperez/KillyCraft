//
//  MapView.cpp
//  KillyCraft
//
//  Created by Ricard Perez del Campo on 25/10/14.
//  Copyright (c) 2014 MelonGames. All rights reserved.
//

#include "MapView.h"
#include "StarsView.h"
#include "base/CCDirector.h"

namespace MelonGames
{
    namespace KillyCraft
    {
        MapView::MapView(const Map* map, cocos2d::Node* mainNode)
        : map(map)
        , starsView(nullptr)
        {
            mainView = cocos2d::Node::create();
            mainView->setContentSize(cocos2d::Director::getInstance()->getWinSize());
            
            mainNode->addChild(mainView);
            
            starsView = new StarsView();
//            starsView->addLayerWithTexture(mainView, std::numeric_limits<int>::min(), "stars1.png", 5.0f, -100.0f);
//            starsView->addLayerWithTexture(mainView, std::numeric_limits<int>::min(), "stars2.png", 0.0f, -140.0f);
//            starsView->addLayerWithTexture(mainView, std::numeric_limits<int>::min(), "stars3.png", -4.0f, -120.0f);
            starsView->addLayerWithTexture(mainView, std::numeric_limits<int>::min(), "background.png", 0.0f, -100.0f);
            
        }
        
        MapView::~MapView()
        {
            delete starsView;
        }
        
        cocos2d::Node* MapView::getNode() const
        {
            return mainView;
        }
        
        void MapView::update(float dt)
        {
            starsView->update(dt);
        }
    }
}