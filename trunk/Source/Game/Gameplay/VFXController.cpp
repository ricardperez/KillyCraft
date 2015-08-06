//
//  VFXController.cpp
//  KillyCraft
//
//  Created by Ricard Perez del Campo on 08/07/15.
//  Copyright (c) 2015 MelonGames. All rights reserved.
//

#include "VFXController.h"
#include "Map.h"
#include "MapObject.h"
#include "Component/PositionComponent.h"
#include "View/MapView.h"
#include "View/StarsView.h"
#include "MelonGames/Random.h"
#include "2d/CCLabel.h"
#include "2d/CCActionInterval.h"
#include "2d/CCActionInstant.h"
#include "2d/CCParticleSystemQuad.h"
#include "2d/CCLayer.h"

namespace MelonGames
{
    namespace KillyCraft
    {
        VFXController::VFXController(Map* map)
        : map(map)
        , opaqueLayer(nullptr)
        {
            
        }
        
        void VFXController::update(float dt)
        {
            updateParticleSystems(dt);
            updateFireWorks(dt);
        }
        
        void VFXController::showScoreNode(int score, const cocos2d::Vec2& position, bool moveUp)
        {
            auto label = cocos2d::Label::createWithTTF(std::to_string(score), "Marker Felt.ttf", 25.0f);
            label->setColor(cocos2d::Color3B::WHITE);
            label->setPosition(position);
            label->setAnchorPoint(cocos2d::Vec2(0.0f, 1.0f));
            map->getView()->getNode()->addChild(label);
            
            cocos2d::Vec2 offset;
            if (moveUp)
            {
                offset.x = Random::getInstance().nextRealInRange(-10.0f, 10.0f);
                offset.y = Random::getInstance().nextRealInRange(65.0f, 100.0f);
            }
            
            label->runAction(cocos2d::Sequence::create(cocos2d::Spawn::create(cocos2d::MoveBy::create(1.0f, offset),
                                                                              cocos2d::FadeOut::create(1.0f),
                                                                              nullptr),
                                                       cocos2d::RemoveSelf::create(),
                                                       nullptr));
        }
        
        void VFXController::showParticleSystem(const std::string& plistName, const cocos2d::Vec2& position, bool animateWithBackground)
        {
            auto particleSystem = cocos2d::ParticleSystemQuad::create(plistName);
            particleSystem->setPosition(position);
            particleSystem->setAutoRemoveOnFinish(true);
            map->getView()->getNode()->addChild(particleSystem);
            
            if (animateWithBackground)
            {
                particleSystem->retain();
                movingParticleSystems.push_back(particleSystem);
            }
        }
        
        void VFXController::showFireWorks(int n)
        {
            static std::vector<cocos2d::Color4F> colors = {
                cocos2d::Color4F::WHITE,
                cocos2d::Color4F::YELLOW,
                cocos2d::Color4F::BLUE,
                cocos2d::Color4F::GREEN,
                cocos2d::Color4F::RED,
                cocos2d::Color4F::MAGENTA,
                cocos2d::Color4F::BLACK,
                cocos2d::Color4F::ORANGE,
                cocos2d::Color4F::GRAY,
            };
            for (int i=0; i<n; ++i)
            {
                FireWorks::Definition definition;
                cocos2d::Node* node = map->getView()->getNode();
                
                definition.rocketParticleSystemName = "fireworks_rocket.plist";
                definition.explosionParticleSystemName = "fireworks_explosion.plist";
                
                definition.startDelay = Random::getInstance().nextRealInRange(0.0f, n/5.0f);
                definition.rocketStartPosition = cocos2d::Vec2(Random::getInstance().nextRealInRange(0.0f, node->getContentSize().width), -10.0f);
                
                cocos2d::Vec2 endPosition = cocos2d::Vec2(Random::getInstance().nextRealInRange(0.2f, 0.8f) * node->getContentSize().width, Random::getInstance().nextRealInRange(0.6f, 0.85f) * node->getContentSize().height);
                float speed = Random::getInstance().nextRealInRange(450.0f, 600.0f);
                definition.rocketSpeed = ((endPosition - definition.rocketStartPosition).getNormalized() * speed);
                
                float maxY = (Random::getInstance().nextRealInRange(0.45f, 0.75f) * node->getContentSize().height);
                definition.rocketTime = ((maxY - definition.rocketStartPosition.y) / definition.rocketSpeed.y);
                
                definition.explosionStartColor = colors.at(Random::getInstance().nextIntInRange(0, colors.size()-1));
                definition.explosionStartColorVar = colors.at(Random::getInstance().nextIntInRange(0, colors.size()-1));
                
                definition.explosionEndColor = colors.at(Random::getInstance().nextIntInRange(0, colors.size()-1));
                definition.explosionEndColorVar = colors.at(Random::getInstance().nextIntInRange(0, colors.size()-1));
                
                definition.parentNode = node;
                
                fireWorks.push_back(definition);
            }
        }
        
        void VFXController::showOpaqueLayer()
        {
            if (!opaqueLayer)
            {
                opaqueLayer = cocos2d::LayerColor::create(cocos2d::Color4B(0, 0, 0, 100));
                map->getView()->getNode()->addChild(opaqueLayer);
                opaqueLayer->setOpacity(0);
            }
            opaqueLayer->setVisible(true);
            opaqueLayer->runAction(cocos2d::FadeTo::create(0.5f, 100));
        }
        
        void VFXController::hideOpaqueLayer()
        {
            if (opaqueLayer)
            {
                opaqueLayer->runAction(cocos2d::Sequence::create(cocos2d::FadeTo::create(0.5f, 0),
                                                                 cocos2d::Hide::create(),
                                                                 nullptr));
            }
        }
        
        bool VFXController::isPlayingAnything() const
        {
            return (!movingParticleSystems.empty() || !fireWorks.empty());
        }
        
        void VFXController::updateParticleSystems(float dt)
        {
            if (!movingParticleSystems.empty())
            {
                cocos2d::Vec2 movement = (map->getView()->getStarsView()->getSpeedVector() * dt);
                
                auto it = movingParticleSystems.begin();
                while (it != movingParticleSystems.end())
                {
                    cocos2d::ParticleSystemQuad* particleSystem = *it;
                    if (particleSystem->getParent())
                    {
                        particleSystem->setPosition(particleSystem->getPosition() + movement);
                        ++it;
                    }
                    else
                    {
                        particleSystem->release();
                        it = movingParticleSystems.erase(it);
                        
                    }
                }
            }
        }
        
        void VFXController::updateFireWorks(float dt)
        {
            auto it = fireWorks.begin();
            while (it != fireWorks.end())
            {
                auto& activeFireWorks = (*it);
                activeFireWorks.update(dt);
                if (activeFireWorks.isDone())
                {
                    activeFireWorks.release();
                    it = fireWorks.erase(it);
                }
                else
                {
                    ++it;
                }
            }
        }
    }
}