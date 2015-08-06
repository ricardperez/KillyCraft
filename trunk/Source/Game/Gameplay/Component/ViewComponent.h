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
#include "math/CCGeometry.h"

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
        class ViewPart;
		
		class ViewComponent : public Component
		{
		public:
			DECLARE_TYPE_WITH_BASE_TYPE(ViewComponent, Component);
            
            friend Component* ComponentsFactory::createViewComponent(const Json::Value &json);
			
			ViewComponent();
			virtual ~ViewComponent();
			
			virtual void onObjectAttachedToMap() override;
            virtual void onWillDetachFromObject() override;
            void update(float dt) override;
			
            void addPart(ViewPart* part, bool takeOwnership);
            void removePart(ViewPart* part);
            
            const cocos2d::Size& getSize();
            
            void setVisible(bool visible);
            bool isVisible() const;
            
            void setRotateOnMovement(bool truthiness);
			
		protected:
			void onPositionChanged(PositionComponent* posComponent);
			
		private:
            struct ViewPartData
            {
                ViewPart* viewPart;
                bool owned;
            };
            std::vector<ViewPartData> parts;
            
            cocos2d::Size size;
            bool sizeDirty;
            
            bool visible;
            
            bool rotateOnMovement;
            cocos2d::Vec2 previousPosition;
            float rotation;
            
            bool firstFrame;
		};
	}
}

#endif /* defined(__KillyCraft__ViewComponent__) */
