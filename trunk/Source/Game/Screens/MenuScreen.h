//
//  MenuScreen.h
//  KillyCraft
//
//  Created by Ricard Pérez del Campo on 14/10/14.
//
//

#ifndef __KillyCraft__MenuScreen__
#define __KillyCraft__MenuScreen__

#include "Screen.h"

namespace MelonGames
{
	namespace KillyCraft
	{
		class MenuScreen : public Screen
		{
        public:
            DECLARE_TYPE_WITH_BASE_TYPE(MenuScreen, Screen);
            
            static MenuScreen* create();
            
        private:
            virtual bool init() override;
		};
	}
}

#endif /* defined(__KillyCraft__MenuScreen__) */
