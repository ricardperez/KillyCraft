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
            
			static GameScreen* create();
			virtual ~GameScreen();
			
		private:
			GameScreen();
			virtual bool init() override;
			void update(float dt);
			
		private:
			Map* map;
            
            bool dead;
		};
	}
}

#endif /* defined(__KillyCraft__GameScreen__) */
