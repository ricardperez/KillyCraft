//
//  GameScreen.cpp
//  KillyCraft
//
//  Created by Ricard Pérez del Campo on 14/10/14.
//
//

#include "GameScreen.h"
#include "Gameplay/Map.h"
#include "Gameplay/MapObject.h"
#include "Gameplay/Player.h"
#include "Gameplay/SpawnObjectsManager.h"
#include "Gameplay/MapObjectInspector.h"
#include "Gameplay/VFXController.h"
#include "ScreenController.h"
#include "Screens/MenuScreen.h"
#include "base/CCDirector.h"

namespace MelonGames
{
	namespace KillyCraft
	{
		GameScreen* GameScreen::create(const std::string& levelName)
		{
			auto result = new GameScreen();
			if (result && result->init(levelName))
			{
				result->autorelease();
				return result;
			}
			
			delete result;
			return nullptr;
		}
		
		GameScreen::GameScreen()
		: map(nullptr)
        , dead(false)
		{
		}
		
		GameScreen::~GameScreen()
		{
			delete map;
		}
		
		bool GameScreen::init(const std::string& levelName)
		{
            if (Base::init())
			{
                const auto& winSize = cocos2d::Director::getInstance()->getWinSize();
                
                float forcedWidth = 768.0f;
                float scale = winSize.width / forcedWidth;
                float forcedHeight = winSize.height / scale;
                
                MapDefinition mapDefinition;
                mapDefinition.screenSize = cocos2d::Size(forcedWidth, forcedHeight);
                mapDefinition.screenScale = scale;
                mapDefinition.fileName =  levelName;
				map = new Map(mapDefinition);
				
				cocos2d::Node* mapNode = cocos2d::Node::create();
				mapNode->setContentSize(winSize);
				addChild(mapNode);
				
				map->setNode(mapNode);
				map->initialize();
                
                scheduleUpdate();
				
				return true;
			}
			
			return false;
		}
		
		void GameScreen::update(float dt)
		{
            if (dead)
            {
                return;
            }
            
			map->update(dt);
            
            if (map->getPlayer()->getLives() == 0)
            {
                dead = true;
                ScreenController::getInstance()->replaceScreen(MenuScreen::create());
            }
            else
            {
                if (map->getSpawnObjectsManager()->isFinished() && (map->getObjectPassingFilter(MapObjectInspector::isEnemy) == nullptr))
                {
                    ScreenController::getInstance()->replaceScreen(MenuScreen::create());
                }
            }
		}
	}
}