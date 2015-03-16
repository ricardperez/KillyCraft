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
		{
		}
		
		ViewComponent::~ViewComponent()
		{
            for (auto part : parts)
            {
                part->onDetachedFromObject(object);
                part->getNode()->removeFromParent();
                delete part;
            }
		}
		
		void ViewComponent::onObjectAttachedToMap()
		{
			Base::onObjectAttachedToMap();
            
            auto mapViewNode = object->getMap()->getView()->getNode();
            for (auto part : parts)
            {
                part->onAttachedToObject(object);
                mapViewNode->addChild(part->getNode());
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
                part->onDetachedFromObject(object);
                part->getNode()->removeFromParent();
                delete part;
            }
            parts.clear();
            sizeDirty = true;
            Base::onWillDetachFromObject();
        }
        
        void ViewComponent::addPart(ViewPart* part)
        {
            parts.push_back(part);
            if (object && object->getMap())
            {
                part->onAttachedToObject(object);
                
                auto node = part->getNode();
                CCASSERT(node != nullptr, "The ViewPart::node should not be null at this point");
                object->getMap()->getView()->getNode()->addChild(node);
                node->setVisible(visible);
                
                onPositionChanged(object->get<PositionComponent>());
                sizeDirty = true;
            }
        }
        
        void ViewComponent::removePart(ViewPart* part)
        {
            auto it = std::find(parts.begin(), parts.end(), part);
            if (it != parts.end())
            {
                if (object && object->getMap())
                {
                    part->onDetachedFromObject(object);
                    part->getNode()->removeFromParent();
                }
                parts.erase(it);
                delete part;
                sizeDirty = true;
            }
        }
        
		void ViewComponent::onPositionChanged(PositionComponent* positionComponent)
		{
            const cocos2d::Vec3& position = positionComponent->getPosition();
            for (auto part : parts)
            {
                part->getNode()->setPosition(Perspective::screenPosition(position + part->getPositionOffset()));
            }
		}
        
        const cocos2d::Size& ViewComponent::getSize()
        {
            if (sizeDirty)
            {
                size.width = 0.0f;
                size.height = 0.0f;
                for (auto part : parts)
                {
                    size.width = std::max(size.width, part->getNode()->getContentSize().width);
                    size.height = std::max(size.height, part->getNode()->getContentSize().height);
                }
                sizeDirty = false;
            }
            return size;
        }
        
        void ViewComponent::setVisible(bool visible)
        {
            if (visible != this->visible)
            {
                this->visible = visible;
                for (auto part : parts)
                {
                    auto node = part->getNode();
                    CCASSERT(node != nullptr, "The ViewPart::node should not be null at this point");
                    if (node)
                    {
                        node->setVisible(visible);
                    }
                }
            }
        }
        
        bool ViewComponent::isVisible() const
        {
            return visible;
        }
	}
}