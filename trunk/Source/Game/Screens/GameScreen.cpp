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
#include "base/CCDirector.h"

namespace MelonGames
{
	namespace KillyCraft
	{
		GameScreen* GameScreen::create()
		{
			auto result = new GameScreen();
			if (result && result->init())
			{
				result->autorelease();
				return result;
			}
			
			delete result;
			return nullptr;
		}
		
		GameScreen::GameScreen()
		: map(nullptr)
		{
		}
		
		GameScreen::~GameScreen()
		{
			delete map;
		}
		
		bool GameScreen::init()
		{
            if (cocos2d::LayerColor::initWithColor(cocos2d::Color4B::WHITE))
			{
                
                const auto& winSize = cocos2d::Director::getInstance()->getWinSize();
                
                float forcedWidth = 768.0f;
                float scale = winSize.width / forcedWidth;
                float forcedHeight = winSize.height / scale;
                
                MapDefinition mapDefinition;
                mapDefinition.height = 5000.0f;
                mapDefinition.screenSize = cocos2d::Size(forcedWidth, forcedHeight);
                mapDefinition.screenScale = scale;
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
			map->update(dt);
		}
	}
}