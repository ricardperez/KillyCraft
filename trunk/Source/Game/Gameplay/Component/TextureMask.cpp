//
//  TextureMask.cpp
//  KillyCraft
//
//  Created by Ricard Perez del Campo on 01/12/14.
//  Copyright (c) 2014 MelonGames. All rights reserved.
//

#include "TextureMask.h"
#include "math/CCGeometry.h"
#include "platform/CCFileUtils.h"

namespace MelonGames
{
    namespace KillyCraft
    {
        TextureMask::TextureMask()
        : mask(nullptr)
        , width(0)
        , height(0)
        {
        }
        
        TextureMask::~TextureMask()
        {
            delete[] mask;
        }
        
        TextureMask* TextureMask::create(const std::string &maskFile, int nBitsForSize)
        {
            TextureMask* result = new TextureMask();
            if (result && result->init(maskFile, nBitsForSize))
            {
                return result;
            }
            
            delete result;
            return nullptr;
        }
        
        TextureMask* TextureMask::create(const cocos2d::Size& size)
        {
            TextureMask* result = new TextureMask();
            if (result && result->init(size))
            {
                return result;
            }
            
            delete result;
            return nullptr;
        }
        
        bool TextureMask::init(const std::string &maskFile, int nBitsForSize)
        {
            auto byteToBits = [](unsigned char byte, bool* bits) -> void
            {
                bits[0] = byte & 1;
                bits[1] = byte & 2;
                bits[2] = byte & 4;
                bits[3] = byte & 8;
                bits[4] = byte & 16;
                bits[5] = byte & 32;
                bits[6] = byte & 64;
                bits[7] = byte & 128;
            };
            
            cocos2d::Data data = cocos2d::FileUtils::getInstance()->getDataFromFile(maskFile);
            if (data.getSize() > 0)
            {
                unsigned char* bytes = data.getBytes();
                int sizeBytes = ((nBitsForSize * 2) / 8.0f + 0.5f);
                
            }
            return false;
        }
        
        bool TextureMask::init(const cocos2d::Size &size)
        {
            width = size.width;
            height = size.height;
            return true;
        }
        
        bool TextureMask::isOpaqueAt(int x, int y) const
        {
            if (x >= 0 && x < width && y >= 0 && y < height)
            {
                if (!mask)
                {
                    return true;
                }
                
                return mask[width * y + x];
            }
            
            return false;
        }
        
        namespace TextureMaskHelper
        {
            bool textureMaskCollision(const TextureMask& tm1, const TextureMask& tm2, const cocos2d::Vec2& origin1, const cocos2d::Vec2& origin2, const cocos2d::Size& size)
            {
                for (int i=0; i<size.width; ++i)
                {
                    for (int j=0; j<size.height; ++j)
                    {
                        bool masked1 = tm1.isOpaqueAt(origin1.x + i, origin1.y + j);
                        if (masked1)
                        {
                            bool masked2 = tm2.isOpaqueAt(origin2.x + i, origin2.y + j);
                            if (masked2)
                            {
                                return true;
                            }
                        }
                    }
                }
                return false;
            }
            
            bool textureMaskCollision(const TextureMask& tm1, const cocos2d::Vec2& origin1, const cocos2d::Vec2& origin2, const cocos2d::Size& size)
            {
                for (int i=0; i<size.width; ++i)
                {
                    for (int j=0; j<size.height; ++j)
                    {
                        bool masked1 = tm1.isOpaqueAt(origin1.x + i, origin1.y + j);
                        if (masked1)
                        {
                            return true;
                        }
                    }
                }
                return false;
            }
        }
    }
}