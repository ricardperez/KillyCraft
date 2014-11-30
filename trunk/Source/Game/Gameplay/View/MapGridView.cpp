//
//  MapGridView.cpp
//  KillyCraft
//
//  Created by Ricard Perez del Campo on 27/11/14.
//  Copyright (c) 2014 MelonGames. All rights reserved.
//

#include "MapGridView.h"
#include "2d/CCDrawingPrimitives.h"
#include "CCDirector.h"

#ifdef DRAW_MAP_GRID

using namespace cocos2d;

namespace MelonGames
{
    namespace KillyCraft
    {
        MapGridView* MapGridView::create()
        {
            MapGridView* result = new MapGridView();
            if (result && result->init())
            {
                result->autorelease();
                return result;
            }
            
            delete result;
            return nullptr;
        }
        
        bool MapGridView::init()
        {
            if (DrawNode::init())
            {
                const float gridSize = 20.0f;
                const auto color1 = Color4F(0.4f, 0.4f, 0.4f, 0.5f);
                const auto color2 = Color4F(0.8f, 0.8f, 0.8f, 0.5f);
                
                const float width = Director::getInstance()->getWinSize().width;
                const float height = Director::getInstance()->getWinSize().height;
                
                int counter = 0;
                float x = 0.0f;
                while (x <= width)
                {
                    drawLine(Vec2(x, 0.0f), Vec2(x, height), (counter % 5 ? color2 : color1));
                    x += gridSize;
                    ++counter;
                }
                
                counter = 0;
                float y = 0.0f;
                while (y <= height)
                {
                    drawLine(Vec2(0.0f, y), Vec2(width, y), (counter % 5 ? color2 : color1));
                    y += gridSize;
                    ++counter;
                }
                
                return true;
            }
            
            return false;
        }
    }
}

#endif