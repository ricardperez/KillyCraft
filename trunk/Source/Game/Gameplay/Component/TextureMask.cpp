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
        
        TextureMask* TextureMask::create(const std::string &maskFile)
        {
            TextureMask* result = new TextureMask();
            if (result && result->init(maskFile))
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
        
        bool TextureMask::init(const std::string &maskFile)
        {
            auto byteToInt = [](unsigned char byte) -> int
            {
                int result = 0;
                
                int nextP2 = 1;
                for (int i=0; i<8; ++i)
                {
                    if (byte & nextP2)
                    {
                        result += nextP2;
                    }
                    nextP2 <<= 1;
                }
                
                return result;
            };
            
            cocos2d::Data data = cocos2d::FileUtils::getInstance()->getDataFromFile(maskFile);
            if (data.getSize() > 0)
            {
                unsigned char* bytes = data.getBytes();
                
                for (int i=0; i<data.getSize(); ++i)
                {
                    if (i % 8 == 0)
                    {
                        printf("\n");
                    }
                    printf("%i ", byteToInt(bytes[i]));
                }
                printf("\n");
                
                //32 bits for specifying the width and height (2+2 bytes)
                int width = byteToInt(bytes[0])*128 + byteToInt(bytes[1]);
                int height = byteToInt(bytes[2])*128 + byteToInt(bytes[3]);
                
                int byteIndex = 4;
                int bitIndex = 0;
                int bitWeight = 128;
                mask = new bool[width*height];
                for (int y = 0; y < height; ++y)
                {
                    for (int x = 0; x<width; ++x)
                    {
                        mask[y*height + x] = (*(bytes+byteIndex)) & bitWeight;
                        
                        bitWeight /= 2;
                        bitIndex++;
                        
                        if (bitIndex == 7)
                        {
                            bitWeight = 128;
                            bitIndex = 0;
                            ++byteIndex;
                        }
                    }
                }
                
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