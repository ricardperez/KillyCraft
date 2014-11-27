//
//  MapView.cpp
//  KillyCraft
//
//  Created by Ricard Perez del Campo on 25/10/14.
//  Copyright (c) 2014 MelonGames. All rights reserved.
//

#include "MapView.h"
#include "StarsView.h"

#include "Gameplay/Map.h"

#include "base/CCDirector.h"

namespace MelonGames
{
    namespace KillyCraft
    {
        MapView::MapView(const Map* map, cocos2d::Node* mainNode)
        : map(map)
        , starsView(nullptr)
#ifdef DRAW_MAP_GRID
        , gridView(nullptr)
#endif
        {
            mainView = cocos2d::Node::create();
            mainView->setContentSize(map->getDefinition().screenSize);
            mainView->setScale(map->getDefinition().screenScale);
            
            mainNode->addChild(mainView);
            
            starsView = new StarsView();
            starsView->addLayerWithTexture(mainView, std::numeric_limits<int>::min(), "background.png", 0.0f, -100.0f);
            
#ifdef DRAW_MAP_GRID
            gridView = MapGridView::create();
            mainNode->addChild(gridView);
#endif
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