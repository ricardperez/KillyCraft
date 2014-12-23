//
//  ScreenController.h
//  KillyCraft
//
//  Created by Ricard Perez del Campo on 23/12/14.
//  Copyright (c) 2014 MelonGames. All rights reserved.
//

#ifndef __KillyCraft__ScreenController__
#define __KillyCraft__ScreenController__

namespace MelonGames
{
    namespace KillyCraft
    {
        class Screen;
        
        class ScreenController
        {
        public:
            static ScreenController* getInstance();
            
            void replaceScreen(Screen* screen);
            
        private:
            ScreenController();
            
        private:
            Screen* currentScreen;
        };
    }
}

#endif /* defined(__KillyCraft__ScreenController__) */
