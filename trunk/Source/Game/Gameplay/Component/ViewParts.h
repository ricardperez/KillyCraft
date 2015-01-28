//
//  ViewParts.h
//  KillyCraft
//
//  Created by Ricard Perez del Campo on 28/01/15.
//  Copyright (c) 2015 MelonGames. All rights reserved.
//

#ifndef __KillyCraft__ViewParts__
#define __KillyCraft__ViewParts__

#include "MelonGames/DeclaredTypes.h"
#include <string>
#include "math/Vec3.h"

namespace Json
{
    class Value;
}

namespace cocos2d
{
    class Node;
    class Sprite;
    struct Color3B;
}

namespace MelonGames
{
    namespace KillyCraft
    {
        class ViewPart;
        namespace ViewPartsFactory
        {
            ViewPart* createViewPart(const Json::Value& json);
        }
        
        class ViewPart
        {
        public:
            DECLARE_BASE_TYPE(ViewPart);
            
            ViewPart();
            virtual ~ViewPart();
            
            virtual cocos2d::Node* getNode() = 0;
            
            void setPositionOffset(const cocos2d::Vec3& offset);
            const cocos2d::Vec3& getPositionOffset() const;
            
        protected:
            cocos2d::Vec3 positionOffset;
        };
        
        
        class ViewPartSprite : public ViewPart
        {
        public:
            DECLARE_TYPE_WITH_BASE_TYPE(ViewPartSprite, ViewPart);
            
            ViewPartSprite(const std::string& spriteFrameName);
            virtual ~ViewPartSprite();
            
            virtual cocos2d::Node* getNode() override;
            
            void setTintColor(const cocos2d::Color3B& color);
            
        private:
            cocos2d::Sprite* sprite;
        };
    }
}

#endif /* defined(__KillyCraft__ViewParts__) */
