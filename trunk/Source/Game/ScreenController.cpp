//
//  ScreenController.cpp
//  KillyCraft
//
//  Created by Ricard Perez del Campo on 23/12/14.
//  Copyright (c) 2014 MelonGames. All rights reserved.
//

#include "ScreenController.h"
#include "Screens/Screen.h"
#include "base/CCDirector.h"
#include "2d/CCTransition.h"

namespace MelonGames
{
    namespace KillyCraft
    {
        ScreenController::ScreenController()
        : currentScreen(nullptr)
        {
        }
        
        ScreenController* ScreenController::getInstance()
        {
            static ScreenController singleton;
            return &singleton;
        }
        
        void ScreenController::replaceScreen(Screen* screen)
        {
            auto prevScreen = currentScreen;
            currentScreen = screen;
            
            auto scene = cocos2d::Scene::create();
            scene->addChild(screen);
            
            auto director = cocos2d::Director::getInstance();
            if (prevScreen == nullptr)
            {
                director->runWithScene(scene);
            }
            else
            {
                auto transitionScene = cocos2d::TransitionMoveInR::create(0.5f, scene);
                director->replaceScene(transitionScene);
            }
        }
    }
}