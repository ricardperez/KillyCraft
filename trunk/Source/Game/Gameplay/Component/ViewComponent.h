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
#include "base/ccTypes.h"

namespace cocos2d
{
	class Sprite;
	class SpriteFrame;
}

namespace MelonGames
{
	namespace KillyCraft
	{
        namespace ComponentsFactory
        {
            Component* createViewComponent(const Json::Value& json);
        }
        
        class PositionComponent;
		
		class ViewComponent : public Component
		{
		public:
			DECLARE_TYPE_WITH_BASE_TYPE(ViewComponent, Component);
            
            friend class ObjectsFastFactory;
            friend Component* ComponentsFactory::createViewComponent(const Json::Value &json);
			
			ViewComponent();
			virtual ~ViewComponent();
			
			virtual void onObjectAttachedToMap() override;
            virtual void onWillDetachFromObject() override;
			
			const cocos2d::Sprite* getSprite() const;
            
            float getScale() const;
            
            virtual void setTintColor(const cocos2d::Color3B& color);
            const cocos2d::Color3B& getTintColor() const;
			
		protected:
			void onPositionChanged(PositionComponent* posComponent);
			
		private:
			std::string spriteFrameName;
			cocos2d::Sprite* sprite;
            cocos2d::Color3B tint;
		};
	}
}

#endif /* defined(__KillyCraft__ViewComponent__) */
