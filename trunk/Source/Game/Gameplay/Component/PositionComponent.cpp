//
//  PositionComponent.cpp
//  KillyCraft
//
//  Created by Ricard Pérez del Campo on 21/10/14.
//
//

#include "PositionComponent.h"
#include <cmath>

using namespace cocos2d;

namespace MelonGames
{
	namespace KillyCraft
	{
		PositionComponent::PositionComponent()
		: positionSet(false)
        , minX(std::numeric_limits<float>::min())
        , maxX(std::numeric_limits<float>::max())
		{
		}
		
		void PositionComponent::setPosition(const cocos2d::Vec2& p)
		{
            float x = std::max(minX, std::min(maxX, p.x));
            float y = p.y;
            
			float e = std::numeric_limits<float>::min();
			bool changed = ((std::abs(x-position.x) > e) || (std::abs(y-position.y) > e));
            position.set(x, y);
			
			positionSet = true;
			
			if (changed)
			{
				positionChangedSignal.Emit(this);
			}
		}
		
		const cocos2d::Vec2& PositionComponent::getPosition() const
		{
			return position;
		}
        
        void PositionComponent::movePositionX(float x)
        {
            setPosition(position + Vec2(x, 0.0f));
        }
        
        void PositionComponent::movePositionY(float y)
        {
            setPosition(position + Vec2(0.0f, y));
        }
        
        void PositionComponent::movePosition(const cocos2d::Vec2& vec2)
        {
            setPosition(position + vec2);
        }
		
		bool PositionComponent::isPositionSet() const
		{
			return positionSet;
		}
		
		Gallant::Signal1<PositionComponent*>& PositionComponent::getPositionChangedSignal()
		{
			return positionChangedSignal;
		}
        
        void PositionComponent::setMinPositionX(float minX)
        {
            this->minX = minX;
        }
        
        void PositionComponent::setMaxPositionX(float maxX)
        {
            this->maxX = maxX;
        }
	}
}