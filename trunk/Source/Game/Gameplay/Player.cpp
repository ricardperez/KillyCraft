//
//  Player.cpp
//  KillyCraft
//
//  Created by Ricard Pérez del Campo on 24/10/14.
//  Copyright (c) 2014 MelonGames. All rights reserved.
//

#include "Player.h"
#include "Gameplay/Gamepad.h"

namespace MelonGames
{
	namespace KillyCraft
	{
		Player::Player()
        : lives(0)
		{
            gamepad = new Gamepad();
		}
		
		Player::~Player()
		{
			delete gamepad;
		}
		
		Gamepad* Player::getGamepad() const
		{
			return gamepad;
		}
        
        unsigned int Player::getLives() const
        {
            return lives;
        }
        
        Gallant::Signal1<Player*>& Player::getLivesChangedSignal()
        {
            return livesChangedSignal;
        }
        
        void Player::addLives(unsigned int n)
        {
            if (n > 0)
            {
                lives += n;
                livesChangedSignal.Emit(this);
            }
        }
        
        void Player::removeLives(unsigned int n)
        {
            if (n > 0)
            {
                if (n >= lives)
                {
                    lives = 0;
                }
                else
                {
                    lives -= n;
                }
                livesChangedSignal.Emit(this);
            }
        }
	}
}