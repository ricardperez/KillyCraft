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
		namespace Perspective
		{
			cocos2d::Vec2 screenPosition(const cocos2d::Vec3& vec)
			{
				return Vec2(vec.x, vec.y + vec.z*Perspective::kRatio);
			}
			
			cocos2d::Vec2 screenPosition(const cocos2d::Vec2& vec, float height)
			{
				return Vec2(vec.x, vec.y + height*Perspective::kRatio);
			}
		}
		
		PositionComponent::PositionComponent()
		: positionSet(false)
		{
		}
		
		void PositionComponent::setPosition(const cocos2d::Vec3& p)
		{
			float e = std::numeric_limits<float>::min();
			bool changed = ((std::abs(p.x-position.x) > e) || (std::abs(p.y-position.y) > e) || (std::abs(p.z-position.z) > e));
			position = p;
			
			positionSet = true;
			
			if (changed)
			{
				positionChangedSignal.Emit(this);
			}
		}
		
		const cocos2d::Vec3& PositionComponent::getPosition() const
		{
			return position;
		}
        
        cocos2d::Vec2 PositionComponent::getGroundPosition() const
        {
            return Vec2(position.x, position.y);
        }
        
        void PositionComponent::movePositionX(float x)
        {
            setPosition(position + Vec3(x, 0.0f, 0.0f));
        }
        
        void PositionComponent::movePositionY(float y)
        {
            setPosition(position + Vec3(0.0f, y, 0.0f));
        }
        
        void PositionComponent::movePositionZ(float z)
        {
            setPosition(position + Vec3(0.0f, 0.0f, z));
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