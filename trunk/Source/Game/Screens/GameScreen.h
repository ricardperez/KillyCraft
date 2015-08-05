//
//  GameScreen.h
//  KillyCraft
//
//  Created by Ricard Pérez del Campo on 14/10/14.
//
//

#ifndef __KillyCraft__GameScreen__
#define __KillyCraft__GameScreen__

#include "Screen.h"

namespace MelonGames
{
	namespace KillyCraft
	{
		class Map;
		
		class GameScreen : public Screen
		{
		public:
            DECLARE_TYPE_WITH_BASE_TYPE(GameScreen, Screen);
            
            static GameScreen* create(const std::string& levelName);
			virtual ~GameScreen();
			
		private:
			GameScreen();
            bool init(const std::string& levelName);
			void update(float dt);
			
		private:
			Map* map;
            
            bool dead;
            bool won;
		};
	}
}

#endif /* defined(__KillyCraft__GameScreen__) */
