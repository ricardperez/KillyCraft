//
//  Player.cpp
//  KillyCraft
//
//  Created by Ricard Pérez del Campo on 24/10/14.
//  Copyright (c) 2014 MelonGames. All rights reserved.
//

#include "Player.h"
#include "Gameplay/Gamepad.h"
#include "Gameplay/MapObject.h"

namespace MelonGames
{
	namespace KillyCraft
	{
		Player::Player()
        : lives(0)
        , score(0)
        , playerObject(nullptr)
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
        
        int Player::getLives() const
        {
            return lives;
        }
        
        Gallant::Signal1<Player*>& Player::getLivesChangedSignal()
        {
            return livesChangedSignal;
        }
        
        int Player::getScore() const
        {
            return score;
        }
        
        Gallant::Signal1<Player*>& Player::getScoreChangedSignal()
        {
            return scoreChangedSignal;
        }
        
        void Player::addLives(int n)
        {
            if (n > 0)
            {
                lives += n;
                livesChangedSignal.Emit(this);
            }
        }
        
        void Player::removeLives(int n)
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
        
        void Player::addScore(int nPoints)
        {
            score += nPoints;
            scoreChangedSignal.Emit(this);
        }
        
        void Player::setPlayerObject(MapObject* object)
        {
            playerObject = object;
        }
        
        MapObject* Player::getPlayerObject() const
        {
            return playerObject;
        }
	}
}