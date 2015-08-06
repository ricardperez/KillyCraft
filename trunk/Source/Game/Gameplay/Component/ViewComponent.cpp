//
//  ViewComponent.cpp
//  KillyCraft
//
//  Created by Ricard Pérez del Campo on 16/10/14.
//
//

#include "ViewComponent.h"
#include "ViewParts.h"
#include "Gameplay/MapObject.h"
#include "Gameplay/Map.h"
#include "Gameplay/View/MapView.h"
#include "PositionComponent.h"

namespace MelonGames
{
	namespace KillyCraft
	{
		ViewComponent::ViewComponent()
        : sizeDirty(true)
        , visible(true)
        , rotateOnMovement(false)
        , rotation(0.0f)
        , firstFrame(true)
		{
		}
		
		ViewComponent::~ViewComponent()
		{
            for (auto& part : parts)
            {
                part.viewPart->onDetachedFromObject(object);
                part.viewPart->getNode()->removeFromParent();
                if (part.owned)
                {
                    delete part.viewPart;
                }
            }
		}
		
		void ViewComponent::onObjectAttachedToMap()
		{
			Base::onObjectAttachedToMap();
            
            auto mapViewNode = object->getMap()->getView()->getNode();
            for (auto& part : parts)
            {
                part.viewPart->onAttachedToObject(object);
                mapViewNode->addChild(part.viewPart->getNode());
                
                if (firstFrame && rotateOnMovement)
                {
                    part.viewPart->getNode()->setVisible(false);
                }
                
            }
            sizeDirty = true;
            
            auto positionComponent = object->getOrCreate<PositionComponent>();
            positionComponent->getPositionChangedSignal().Connect(this, &ViewComponent::onPositionChanged);
            if (positionComponent->isPositionSet())
            {
                onPositionChanged(positionComponent);
            }
		}
        
        void ViewComponent::onWillDetachFromObject()
        {
            for (auto part : parts)
            {
                part.viewPart->onDetachedFromObject(object);
                part.viewPart->getNode()->removeFromParent();
                if (part.owned)
                {
                    delete part.viewPart;
                }
            }
            parts.clear();
            sizeDirty = true;
            Base::onWillDetachFromObject();
        }
        
        void ViewComponent::update(float dt)
        {
            Base::update(dt);
            
            if (firstFrame)
            {
                firstFrame = false;
                visible = !visible;
                setVisible(!visible);
            }
        }
        
        void ViewComponent::addPart(ViewPart* part, bool takeOwnership)
        {
            ViewPartData partData;
            partData.viewPart = part;
            partData.owned = takeOwnership;
            parts.push_back(partData);
            
            if (object && object->getMap())
            {
                part->onAttachedToObject(object);
                
                auto node = part->getNode();
                CCASSERT(node != nullptr, "The ViewPart::node should not be null at this point");
                object->getMap()->getView()->getNode()->addChild(node);
                if (firstFrame && rotateOnMovement)
                {
                    node->setVisible(false);
                }
                else
                {
                    node->setVisible(visible);
                }
                
                auto positionComponent = object->get<PositionComponent>();
                previousPosition = positionComponent->getPosition();
                onPositionChanged(positionComponent);
                sizeDirty = true;
            }
        }
        
        void ViewComponent::removePart(ViewPart* part)
        {
            auto it = std::find_if(parts.begin(), parts.end(), [part](const ViewPartData& partData)->bool {
                return (partData.viewPart == part);
            });
            
            if (it != parts.end())
            {
                const ViewPartData& partData = *it;
                if (object && object->getMap())
                {
                    part->onDetachedFromObject(object);
                    part->getNode()->removeFromParent();
                }
                if (partData.owned)
                {
                    delete partData.viewPart;
                }
                parts.erase(it);
                sizeDirty = true;
            }
        }
        
		void ViewComponent::onPositionChanged(PositionComponent* positionComponent)
		{
            const cocos2d::Vec2& position = positionComponent->getPosition();
            
            if (rotateOnMovement)
            {
                if (position.getDistanceSq(previousPosition) > std::numeric_limits<float>::epsilon())
                {
                    rotation = (-CC_RADIANS_TO_DEGREES((position - previousPosition).getAngle()) + 90.0f);
                }
            }
            
            for (auto& part : parts)
            {
                auto node = part.viewPart->getNode();
                node->setPosition(position + part.viewPart->getPositionOffset());
                node->setRotation(rotation);
            }
            
            previousPosition = position;
		}
        
        const cocos2d::Size& ViewComponent::getSize()
        {
            if (sizeDirty)
            {
                size.width = 0.0f;
                size.height = 0.0f;
                for (auto& part : parts)
                {
                    size.width = std::max(size.width, part.viewPart->getNode()->getContentSize().width);
                    size.height = std::max(size.height, part.viewPart->getNode()->getContentSize().height);
                }
                sizeDirty = false;
            }
            return size;
        }
        
        void ViewComponent::setVisible(bool visible)
        {
            if (firstFrame && rotateOnMovement)
            {
                this->visible = visible;
                return;
            }
            else
            {
                if (visible != this->visible)
                {
                    this->visible = visible;
                    for (auto& part : parts)
                    {
                        auto node = part.viewPart->getNode();
                        CCASSERT(node != nullptr, "The ViewPart::node should not be null at this point");
                        if (node)
                        {
                            node->setVisible(visible);
                        }
                    }
                }
            }
        }
        
        bool ViewComponent::isVisible() const
        {
            return visible;
        }
        
        void ViewComponent::setRotateOnMovement(bool truthiness)
        {
            rotateOnMovement = truthiness;
        }
	}
}