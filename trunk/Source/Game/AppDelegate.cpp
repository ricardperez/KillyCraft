#include "AppDelegate.h"
#include "ScreenController.h"
#include "Screens/MenuScreen.h"
#include "MelonGames/Services/ServicesManager.h"
#include "MelonGames/Services/FilesService.h"

namespace MelonGames
{
	namespace KillyCraft
	{
		USING_NS_CC;
		
		AppDelegate::AppDelegate() {
			
		}
		
		AppDelegate::~AppDelegate()
		{
		}
		
		bool AppDelegate::applicationDidFinishLaunching()
		{
			// initialize director
			auto director = Director::getInstance();
			auto glview = director->getOpenGLView();
			if(!glview) {
				glview = GLViewImpl::create("KillyCraft");
				director->setOpenGLView(glview);
			}
			
			// turn on display FPS
//			director->setDisplayStats(true);
			
			// set FPS. the default value is 1.0/60 if you don't call this
			director->setAnimationInterval(1.0 / 60);
			
            cocos2d::Size winSize = Director::getInstance()->getWinSizeInPixels();
            float width = std::max(winSize.width, winSize.height);
            if (width > 1024.0f)
            {
                director->setContentScaleFactor(2.0f);
            }
            else
            {
                director->setContentScaleFactor(1.0f);
            }
            
			createServices();
			
            ScreenController::getInstance()->replaceScreen(MenuScreen::create());
			
			return true;
		}
		
		// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
		void AppDelegate::applicationDidEnterBackground()
		{
			Director::getInstance()->stopAnimation();
			
			// if you use SimpleAudioEngine, it must be pause
			// SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
		}
		
		// this function will be called when the app is active again
		void AppDelegate::applicationWillEnterForeground()
		{
			Director::getInstance()->startAnimation();
			
			// if you use SimpleAudioEngine, it must resume here
			// SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
		}
		
		void AppDelegate::createServices()
		{
			auto& servicesManager = ServicesManager::getInstance();
			
			FilesService* filesService = new FilesService();
            if (Director::getInstance()->getContentScaleFactor() == 1.0f)
            {
                filesService->addDirectory("SD/");
            }
            else
            {
                filesService->addDirectory("HD/");
            }
            filesService->addDirectory("Common/");
            filesService->addDirectory("bin/");
            filesService->addDirectory("fonts/");
			servicesManager.add(filesService);
		}
	}
}
