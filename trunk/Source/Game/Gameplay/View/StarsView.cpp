//
//  StarsView.cpp
//  KillyCraft
//
//  Created by Ricard Perez del Campo on 25/10/14.
//  Copyright (c) 2014 MelonGames. All rights reserved.
//

#include "StarsView.h"
#include "2d/CCSprite.h"
#include "renderer/CCTextureCache.h"
#include "base/CCDirector.h"

namespace MelonGames
{
    namespace KillyCraft
    {
        StarsView::StarsView()
        : speedMultiplier(1.0f)
        {
            
        }
        
        StarsView::~StarsView()
        {
            for (auto& layer : layers)
            {
                layer.sprite->removeFromParent();
            }
        }
        
        void StarsView::update(float dt)
        {
            for (auto& layer : layers)
            {
                const cocos2d::Rect& lastRect = layer.sprite->getTextureRect();
                cocos2d::Rect nextRect = lastRect;
                nextRect.origin.x += (dt * layer.speedX * speedMultiplier);
                nextRect.origin.y += (dt * layer.speedY * speedMultiplier);
                
                layer.sprite->setTextureRect(nextRect);
            }
        }
        
        void StarsView::addLayerWithTexture(cocos2d::Node* operatingNode, int zOrder, const std::string& textureName, float speedX, float speedY)
        {
            Layer layer;
            layer.speedX = speedX;
            layer.speedY = speedY;
            
            cocos2d::Texture2D* texture = cocos2d::Director::getInstance()->getTextureCache()->addImage(textureName);
            assert(texture);
            texture->setTexParameters({GL_LINEAR,GL_LINEAR,GL_REPEAT,GL_REPEAT});
            cocos2d::Rect rect(0.0f, 0.0f, operatingNode->getContentSize().width, operatingNode->getContentSize().height);
            layer.sprite = cocos2d::Sprite::createWithTexture(texture, rect);
            operatingNode->addChild(layer.sprite, zOrder);
            layer.sprite->setPosition(operatingNode->getContentSize()*0.5f);
            
            layers.push_back(layer);
        }
        
        void StarsView::setSpeedMultiplier(float multiplier)
        {
            speedMultiplier = multiplier;
        }
    }
}