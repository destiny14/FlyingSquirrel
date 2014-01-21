#ifndef __MAINMENU_H__
#define __MAINMENU_H__

#include "cocos2d.h"

class CMainMenu : public cocos2d::Layer {

public:
	static cocos2d::Scene* createMainMenuScene();
	virtual bool init();

	void startCallback(Object* sender);
	void exitCallback(Object* sender);

	CREATE_FUNC(CMainMenu);
};

#endif