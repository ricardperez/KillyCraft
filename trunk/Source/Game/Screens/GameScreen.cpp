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
			if (cocos2d::Layer::create())
			{
                MapDefinition mapDefinition;
                mapDefinition.height = 5000.0f;
				map = new Map(mapDefinition);
				
				cocos2d::Node* mapNode = cocos2d::Node::create();
				mapNode->setPosition(getContentSize()*0.5f);
				mapNode->setContentSize(getContentSize());
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