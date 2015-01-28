//
//  MoveActions.cpp
//  KillyCraft
//
//  Created by Ricard Perez del Campo on 20/01/15.
//  Copyright (c) 2015 MelonGames. All rights reserved.
//

#include "MoveActions.h"
#include "Gameplay/MapObject.h"
#include "Gameplay/Map.h"
#include "Gameplay/Component/PositionComponent.h"
#include "Gameplay/Component/ViewComponent.h"
#include "math/Vec3.h"
#include "2d/CCSprite.h"

namespace MelonGames
{
    namespace KillyCraft
    {
        namespace MoveActions
        {
            void moveByVector(MapObject* object, const cocos2d::Vec3& vector)
            {
                moveByVector(object, vector.x, vector.y, vector.z);
            }
            
            void moveByVector(MapObject* object, float x, float y, float z)
            {
                if (auto posComponent = object->get<PositionComponent>())
                {
                    cocos2d::Vec3 positionCp = posComponent->getPosition();
                    
                    if (std::abs(x) > std::numeric_limits<float>::epsilon())
                    {
                        float viewComponentWidth = 0.0f;
                        if (auto viewComponent = object->get<ViewComponent>())
                        {
                            viewComponentWidth = viewComponent->getSize().width;
                        }
                        
                        float desiredX = positionCp.x + x;
                        float maxX = (object->getMap()->getDefinition().screenSize.width - viewComponentWidth * 0.45f);
                        float minX = (viewComponentWidth * 0.45f);
                        
                        positionCp.x = std::max(minX, std::min(maxX, desiredX));
                    }
                    
                    positionCp.y += y;
                    positionCp.z += z;
                    
                    posComponent->setPosition(positionCp);
                }
            }
            
            void moveByVector(MapObject* object, float x, float y)
            {
                moveByVector(object, x, y, 0.0f);
            }
            
            void moveOnX(MapObject* object, float x)
            {
                moveByVector(object, x, 0.0f, 0.0f);
            }
            
            void moveOnY(MapObject* object, float y)
            {
                moveByVector(object, 0.0f, y, 0.0f);
            }
        }
    }
}