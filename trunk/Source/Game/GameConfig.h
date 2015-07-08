//
//  GameConfig.h
//  KillyCraft
//
//  Created by Ricard Perez del Campo on 11/11/14.
//  Copyright (c) 2014 MelonGames. All rights reserved.
//

#ifdef CC_TARGET_OS_IPHONE
#include "TargetConditionals.h" //to access TARGET_IPHONE_SIMULATOR
#endif

#ifndef KillyCraft_GameConfig_h
#define KillyCraft_GameConfig_h

//#define FORCED_SQUAD "SquadBasic-1"
//#define DRAW_MAP_GRID
//#define DRAW_COLLISION_BOXES

#if TARGET_IPHONE_SIMULATOR
#define USE_GAMEPAD_SHOOT_BUTTON
#endif

#endif
