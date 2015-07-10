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
#include "libs/Signal/Signal.h"

namespace MelonGames
{
	namespace KillyCraft
	{
        namespace ComponentsFactory
        {
            Component* createPositionComponent(const Json::Value& json);
        }
        
		class PositionComponent : public Component
		{
		public:
			DECLARE_TYPE_WITH_BASE_TYPE(PositionComponent, Component);
            
            friend Component* ComponentsFactory::createPositionComponent(const Json::Value& json);
			
			PositionComponent();
			
			void setPosition(const cocos2d::Vec2& p);
			const cocos2d::Vec2& getPosition() const;
            
            void movePositionX(float x);
            void movePositionY(float y);
            void movePosition(const cocos2d::Vec2& vec2);
            
			bool isPositionSet() const;
			
			Gallant::Signal1<PositionComponent*>& getPositionChangedSignal();
			
		private:
			cocos2d::Vec2 position;
			Gallant::Signal1<PositionComponent*> positionChangedSignal;
			bool positionSet;
		};
	}
}

#endif /* defined(__KillyCraft__PositionComponent__) */
