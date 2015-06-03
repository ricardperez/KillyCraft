//
//  ViewParts.cpp
//  KillyCraft
//
//  Created by Ricard Perez del Campo on 28/01/15.
//  Copyright (c) 2015 MelonGames. All rights reserved.
//

#include "ViewParts.h"
#include "Gameplay/MapObject.h"
#include "WeaponComponent.h"
#include "MelonGames/SpriteFrameHelper.h"
#include "MelonGames/Crypto.h"
#include "2d/CCSprite.h"
#include "2d/CCSpriteFrame.h"
#include "2d/CCLabel.h"
#include "json/value.h"
#include "base/ccMacros.h"
#include "2d/CCParticleSystemQuad.h"

namespace MelonGames
{
    namespace KillyCraft
    {
#pragma mark - ViewPartsFactory
        namespace ViewPartsFactory
        {
            ViewPart* createViewPartSprite(const Json::Value& json)
            {
                std::string spriteFrameName = json["sprite"].asString();
                ViewPartSprite* result = new ViewPartSprite(spriteFrameName);
                
                const Json::Value& tintValue = json["tint"];
                if (!tintValue.isNull())
                {
                    result->setTintColor(cocos2d::Color3B(tintValue[0].asInt(), tintValue[1].asInt(), tintValue[2].asInt()));
                }
                
                return result;
            }
            
            ViewPart* createViewPartWeapon(const Json::Value& json)
            {
                ViewPartWeapon* result = new ViewPartWeapon();
                return result;
            }
            
            ViewPart* createViewPartParticleSystem(const Json::Value& json)
            {
                std::string fileName = json["file"].asString();
                ViewPartParticleSystem* result = new ViewPartParticleSystem(fileName);
                return result;
            }
            
            void configureViewPartBase(ViewPart* viewPart, const Json::Value& json)
            {
                float offsetX = json["offset"][0].asFloat();
                float offsetY = json["offset"][1].asFloat();
                float offsetZ = json["offset"][2].asFloat();
                viewPart->setPositionOffset(cocos2d::Vec3(offsetX, offsetY, offsetZ));
            }
            
            ViewPart* createViewPart(const Json::Value& json)
            {
                static std::map<unsigned int, std::function<ViewPart*(const Json::Value&)>> lambdas = {
                    {Crypto::stringHash("Sprite"), createViewPartSprite},
                    {Crypto::stringHash("Weapon"), createViewPartWeapon},
                    {Crypto::stringHash("Particles"), createViewPartParticleSystem},
                };
                
                ViewPart* result = nullptr;
                
                std::string type = json["type"].asString();
                unsigned int key = Crypto::stringHash(type);
                
                auto lambdaIt = lambdas.find(key);
                if (lambdaIt != lambdas.end())
                {
                    result = lambdaIt->second(json);
                }
                
                if (result)
                {
                    configureViewPartBase(result, json);
                    return result;
                }
                
                CCASSERT(false, ("Could not create a ViewPart of type " + type).c_str());
                return nullptr;
            }
        }
        
#pragma mark - ViewPart
        ViewPart::ViewPart()
        {
            
        }
        
        ViewPart::~ViewPart()
        {
        }
        
        void ViewPart::setPositionOffset(const cocos2d::Vec3& offset)
        {
            positionOffset = offset;
        }
        
        const cocos2d::Vec3& ViewPart::getPositionOffset() const
        {
            return positionOffset;
        }
        
        void ViewPart::onAttachedToObject(MapObject* object)
        {
        }
        
        void ViewPart::onDetachedFromObject(MapObject* object)
        {
        }
        
#pragma mark - ViewPartSprite
        ViewPartSprite::ViewPartSprite(const std::string& spriteFrameName)
        {
            sprite = cocos2d::Sprite::createWithSpriteFrame(spriteFrameOrDefault(spriteFrameName));
            sprite->retain();
        }
        
        ViewPartSprite::~ViewPartSprite()
        {
            sprite->release();
        }
        
        cocos2d::Node* ViewPartSprite::getNode()
        {
            return sprite;
        }
        
        void ViewPartSprite::setTintColor(const cocos2d::Color3B& color)
        {
            sprite->setColor(color);
        }
        
#pragma mark - ViewPartParticleSystem
        ViewPartParticleSystem::ViewPartParticleSystem(const std::string& fileName)
        {
            particleSystem = cocos2d::ParticleSystemQuad::create(fileName);
            particleSystem->setPositionType(cocos2d::ParticleSystem::PositionType::GROUPED);
            particleSystem->retain();
        }
        
        ViewPartParticleSystem::~ViewPartParticleSystem()
        {
            particleSystem->release();
        }
        
        cocos2d::Node* ViewPartParticleSystem::getNode()
        {
            return particleSystem;
        }
        
#pragma mark - ViewPartWeapon
        ViewPartWeapon::ViewPartWeapon()
        {
            label = cocos2d::Label::createWithTTF("", "Marker Felt.ttf", 25.0f);
            label->setColor(cocos2d::Color3B(0, 0, 0));
            label->retain();
        }
        
        ViewPartWeapon::~ViewPartWeapon()
        {
            label->release();
        }
        
        cocos2d::Node* ViewPartWeapon::getNode()
        {
            return label;
        }
        
        void ViewPartWeapon::onAttachedToObject(MapObject* object)
        {
            Base::onAttachedToObject(object);
            
            if (WeaponComponent* weaponComponent = object->get<WeaponComponent>())
            {
                weaponComponent->getChangedSignal().Connect(this, &ViewPartWeapon::onWeaponComponentChanged);
                label->setString(std::to_string(weaponComponent->getNBullets()));
            }
        }
        
        void ViewPartWeapon::onDetachedFromObject(MapObject* object)
        {
            if (WeaponComponent* weaponComponent = object->get<WeaponComponent>())
            {
                weaponComponent->getChangedSignal().Disconnect(this, &ViewPartWeapon::onWeaponComponentChanged);
            }
            Base::onDetachedFromObject(object);
        }
        
        void ViewPartWeapon::onWeaponComponentChanged(WeaponComponent* weaponComponent)
        {
            label->setString(std::to_string(weaponComponent->getNBullets()));
        }
    }
}