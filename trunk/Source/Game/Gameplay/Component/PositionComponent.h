//
//  PositionComponent.h
//  KillyCraft
//
//  Created by Ricard Pérez del Campo on 21/10/14.
//
//

#ifndef __KillyCraft__PositionComponent__
#define __KillyCraft__PositionComponent__

#include "Component.h"
#include "math/Vec2.h"
#include "math/Vec3.h"
#include "libs/Signal/Signal.h"

namespace MelonGames
{
	namespace KillyCraft
	{
		class PositionComponent : public Component
		{
		public:
			DECLARE_TYPE_WITH_BASE_TYPE(PositionComponent, Component);
			
			PositionComponent();
			
			void setPosition(const cocos2d::Vec3& p);
			const cocos2d::Vec3& getPosition() const;
            cocos2d::Vec2 getGroundPosition() const;
            
            void movePositionX(float x);
            void movePositionY(float y);
            void movePositionZ(float z);
            
			bool isPositionSet() const;
			
			Gallant::Signal1<PositionComponent*>& getPositionChangedSignal();
			
		private:
			cocos2d::Vec3 position;
			Gallant::Signal1<PositionComponent*> positionChangedSignal;
			bool positionSet;
		};
		
		namespace Perspective
		{
			cocos2d::Vec2 screenPosition(const cocos2d::Vec3& vec);
			cocos2d::Vec2 screenPosition(const cocos2d::Vec2& vec, float height);
			
			const float kRatio = 0.5f;
		}
	}
}

#endif /* defined(__KillyCraft__PositionComponent__) */
