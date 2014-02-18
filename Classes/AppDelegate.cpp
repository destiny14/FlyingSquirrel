#include "AppDelegate.h"
#include "MainMenu.h"
#include <fstream>

USING_NS_CC;

AppDelegate::AppDelegate() {
	m_desiredFPS = 60;
}

AppDelegate::~AppDelegate() 
{
}

void AppDelegate::setDesiredFPS(int fps)
{
	if(fps > 0)
		m_desiredFPS = fps;
	// set FPS. the default value is 1.0/60 if you don't call this
	Director::getInstance()->setAnimationInterval(1.0 / m_desiredFPS);
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto eglView = EGLView::getInstance();

    director->setOpenGLView(eglView);
	eglView->setDesignResolutionSize(1600.0f, 1200.0f, ResolutionPolicy::EXACT_FIT);

    // turn on display FPS
    director->setDisplayStats(true);

	setDesiredFPS(-1);

    // create a scene. it's an autorelease object
	auto menu = CMainMenu::createMainMenuScene();

	std::ifstream FileTest("version");
	if (!FileTest)
	{
		log("!!! version file not found\n!!! please update your resources");
		std::exit(0);
	}

	if (FileTest.is_open())
	{
		std::string str;
		std::getline(FileTest, str);
		char* v;
		v = &str[0];
		log("resource version: %s", static_cast<char*>(v));
		if (strcmp(v, RES_VERSION) == 0)
		{
			log("your resources are up-to-date");
		}
	}
	else
	{
		log("!!! could not open version file\n!!! consider updating your resources");
	}

    // run
    director->runWithScene(menu);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
