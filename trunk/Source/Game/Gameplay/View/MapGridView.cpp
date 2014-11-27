//
//  MapGridView.cpp
//  KillyCraft
//
//  Created by Ricard Perez del Campo on 27/11/14.
//  Copyright (c) 2014 MelonGames. All rights reserved.
//

#include "MapGridView.h"
#include "2d/CCDrawingPrimitives.h"

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
                drawLine(Vec2(100.0f, 0.0f), Vec2(100.0f, 500.0f), Color4F(0.0f, 0.0f, 0.0f, 1.0f));
                return true;
            }
            
            return false;
        }
    }
}

#endif