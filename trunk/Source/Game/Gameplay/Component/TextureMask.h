//
//  CollisionDetectionMask.h
//  KillyCraft
//
//  Created by Ricard Perez del Campo on 01/12/14.
//  Copyright (c) 2014 MelonGames. All rights reserved.
//

#ifndef __KillyCraft__TextureMask__
#define __KillyCraft__TextureMask__

#include <string>

namespace cocos2d
{
    class Texture2D;
    class Rect;
    class Size;
    class Vec2;
}

namespace MelonGames
{
    namespace KillyCraft
    {
        class TextureMask
        {
        public:
            static TextureMask* create(const std::string& maskFile);
            static TextureMask* create(const cocos2d::Size& size);
            
            virtual ~TextureMask();
            
            int getWidth() const { return width; }
            int getHeight() const { return height; }
            
            bool isPixelPerfect() const { return (mask != nullptr); }
            
            bool isOpaqueAt(int x, int y) const;
            
        private:
            TextureMask();
            bool init(const std::string& maskFile);
            bool init(const cocos2d::Size& size);
            
        private:
            bool* mask;
            int width;
            int height;
            std::string name;
        };
        
        namespace TextureMaskHelper
        {
            bool textureMaskCollision(const TextureMask& tm1, const TextureMask& tm2, const cocos2d::Vec2& origin1, const cocos2d::Vec2& origin2, const cocos2d::Size& size);
            bool textureMaskCollision(const TextureMask& tm1, const cocos2d::Vec2& origin1, const cocos2d::Vec2& origin2, const cocos2d::Size& size);
        }
    }
}

#endif /* defined(__KillyCraft__TextureMask__) */
