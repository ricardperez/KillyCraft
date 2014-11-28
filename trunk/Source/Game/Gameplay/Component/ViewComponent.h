//
//  ViewComponent.h
//  KillyCraft
//
//  Created by Ricard Pérez del Campo on 16/10/14.
//
//

#ifndef __KillyCraft__ViewComponent__
#define __KillyCraft__ViewComponent__

#include "Component.h"

namespace cocos2d
{
	class Sprite;
	class SpriteFrame;
}

namespace MelonGames
{
	namespace KillyCraft
	{
		class PositionComponent;
		
		class ViewComponent : public Component
		{
		public:
			DECLARE_TYPE_WITH_BASE_TYPE(ViewComponent, Component);
			
			ViewComponent();
			virtual ~ViewComponent();
			
			virtual void onObjectAttachedToMap() override;
            virtual void onWillDetachFromObject() override;
			
			void setSpriteFrameName(const std::string& name);
            
            cocos2d::Sprite* getSprite() const;
            
            float getScale() const;
			
		protected:
			void onPositionChanged(PositionComponent* posComponent);
			
		private:
			std::string spriteFrameName;
			cocos2d::Sprite* sprite;
		};
		
		namespace CocosUtil
		{
			cocos2d::SpriteFrame* spriteFrameOrDefault(const std::string& name);
		}
	}
}

#endif /* defined(__KillyCraft__ViewComponent__) */
