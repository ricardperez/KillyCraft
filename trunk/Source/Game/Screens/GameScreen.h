//
//  GameScreen.h
//  KillyCraft
//
//  Created by Ricard Pérez del Campo on 14/10/14.
//
//

#ifndef __KillyCraft__GameScreen__
#define __KillyCraft__GameScreen__

#include "2d/CCLayer.h"

namespace MelonGames
{
	namespace KillyCraft
	{
		class Map;
		
		class GameScreen : public cocos2d::Layer
		{
		public:
			static GameScreen* create();
			virtual ~GameScreen();
			
		private:
			GameScreen();
			bool init() override;
			void update(float dt);
			
		private:
			Map* map;
		};
	}
}

#endif /* defined(__KillyCraft__GameScreen__) */
