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
#include "extensions/GUI/CCScrollView/CCScrollView.h"
#include "MelonGames/StringUtils.h"
#include "2d/CCDrawNode.h"

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
                std::vector<std::string> levelNames = {
                    "levels/Level1.kc",
                    "levels/Level2.kc",
                };
                
                cocos2d::Vector<cocos2d::MenuItem*> menuItems;
                for (const auto& levelName : levelNames)
                {
                    std::string fileName = StringUtils::split(levelName, "/").back();
                    auto label = cocos2d::Label::createWithTTF(fileName, "Marker Felt.ttf", 50.0f);
                    auto menuItem = cocos2d::MenuItemLabel::create(label, [levelName](cocos2d::Ref* ref) -> void {
                        GameScreen* gameScreen = GameScreen::create(levelName);
                        ScreenController::getInstance()->replaceScreen(gameScreen);
                    });
                    menuItems.pushBack(menuItem);
                }
                
                auto menu = cocos2d::Menu::createWithArray(menuItems);
                menu->alignItemsVerticallyWithPadding(25.0f);
                menu->setPosition(getContentSize()*0.5f);
                
                addChild(menu);
                
                return true;
            }
            
            return false;
        }
    }
}