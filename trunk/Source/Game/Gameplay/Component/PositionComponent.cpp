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
		{
		}
		
		void PositionComponent::setPosition(const cocos2d::Vec2& p)
		{
			float e = std::numeric_limits<float>::min();
			bool changed = ((std::abs(p.x-position.x) > e) || (std::abs(p.y-position.y) > e));
			position = p;
			
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
	}
}