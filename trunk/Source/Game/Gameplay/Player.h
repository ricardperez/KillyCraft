//
//  Player.h
//  KillyCraft
//
//  Created by Ricard Pérez del Campo on 24/10/14.
//  Copyright (c) 2014 MelonGames. All rights reserved.
//

#ifndef __KillyCraft__Player__
#define __KillyCraft__Player__

namespace MelonGames
{
	namespace KillyCraft
	{
		class GamepadController;
		
		class Player
		{
		public:
			Player();
			virtual ~Player();
			
			GamepadController* getGamepadController() const;
			
		private:
			GamepadController* gamepadController;
		};
	}
}

#endif /* defined(__KillyCraft__Player__) */
