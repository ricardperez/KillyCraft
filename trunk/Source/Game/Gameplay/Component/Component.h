//
//  Component.h
//  KillyCraft
//
//  Created by Ricard Pérez del Campo on 16/10/14.
//
//

#ifndef __KillyCraft__Component__
#define __KillyCraft__Component__

#include "MelonGames/DeclaredTypes.h"

namespace MelonGames
{
	namespace KillyCraft
	{
		class MapObject;
        
        class Component
		{
		public:
			DECLARE_BASE_TYPE(Component);
			
			Component();
			virtual ~Component();
			
			virtual void onAttachedToObject(MapObject* o);
			virtual void onObjectAttachedToMap();
			virtual void onWillDetachFromObject();
			
			virtual void update(float dt);
            
            MapObject* getObject() const;
			
		protected:
			MapObject* object;
		};
	}
}

#endif /* defined(__KillyCraft__Component__) */
