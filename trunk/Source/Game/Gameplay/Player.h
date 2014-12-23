//
//  Player.h
//  KillyCraft
//
//  Created by Ricard Pérez del Campo on 24/10/14.
//  Copyright (c) 2014 MelonGames. All rights reserved.
//

#ifndef __KillyCraft__Player__
#define __KillyCraft__Player__

#include "Signal/Signal.h"

namespace MelonGames
{
	namespace KillyCraft
	{
		class Gamepad;
		
		class Player
		{
		public:
			Player();
			virtual ~Player();
			
			Gamepad* getGamepad() const;
            
            unsigned int getLives() const;
            Gallant::Signal1<Player*>& getLivesChangedSignal();
            
            void addLives(unsigned int n);
            void removeLives(unsigned int n);
			
		private:
			Gamepad* gamepad;
            unsigned int lives;
            Gallant::Signal1<Player*> livesChangedSignal;
		};
	}
}

#endif /* defined(__KillyCraft__Player__) */
