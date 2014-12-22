//
//  SpriteFrameHelper.h
//  KillyCraft
//
//  Created by Ricard Perez del Campo on 22/12/14.
//  Copyright (c) 2014 MelonGames. All rights reserved.
//

#ifndef __KillyCraft__SpriteFrameHelper__
#define __KillyCraft__SpriteFrameHelper__

#include <string>

namespace cocos2d
{
    class SpriteFrame;
}

namespace MelonGames
{
    cocos2d::SpriteFrame* spriteFrameOrDefault(const std::string& name);
}

#endif /* defined(__KillyCraft__SpriteFrameHelper__) */
