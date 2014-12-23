//
//  MenuScreen.cpp
//  KillyCraft
//
//  Created by Ricard Pérez del Campo on 14/10/14.
//
//

#include "MenuScreen.h"
#include "ScreenController.h"
#include "GameScreen.h"
#include "2d/CCMenu.h"
#include "2d/CCMenuItem.h"
#include "2d/CCLabel.h"

namespace MelonGames
{
    namespace KillyCraft
    {
        MenuScreen* MenuScreen::create()
        {
            auto result = new MenuScreen();
            if (result && result->init())
            {
                result->autorelease();
                return result;
            }
            
            delete result;
            return nullptr;
        }
        
        bool MenuScreen::init()
        {
            if (Base::init())
            {
                auto label = cocos2d::Label::createWithTTF("Start Game", "Marker Felt.ttf", 50.0f);
                cocos2d::MenuItemLabel* startMenuItem = cocos2d::MenuItemLabel::create(label, [](cocos2d::Ref* ref) -> void {
                    ScreenController::getInstance()->replaceScreen(GameScreen::create());
                });
                cocos2d::Menu* menu = cocos2d::Menu::createWithItem(startMenuItem);
                addChild(menu);
                
                return true;
            }
            
            return false;
        }
    }
}