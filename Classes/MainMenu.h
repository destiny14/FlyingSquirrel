#ifndef __MAINMENU_H__
#define __MAINMENU_H__

#include "cocos2d.h"
#include "Input.h"

class CMainMenu : public cocos2d::Layer {

public:
	static cocos2d::Scene* createMainMenuScene();
	virtual bool init();

	void startCallback(Object* sender);
	void exitCallback(Object* sender);

	void update(float _dt);

	CREATE_FUNC(CMainMenu);
private:
	InputManager* m_pInput;
	InputAction* m_pStartGame;
};

#endif