#include "MainMenu.h"
#include "CommonMain.h"
#include "Logfile.h"
#include "HelloWorldScene.h"
#include "UI.h"

USING_NS_CC;

Scene* CMainMenu::createMainMenuScene()
{
	auto scene = Scene::create();
	auto layer = CMainMenu::create();
	scene->addChild(layer);

	return scene;
}

bool CMainMenu::init()
{
	if (!Layer::init())
        return false;

	initInput();
	ACTIVATEMAINMENUUI(this);

	this->scheduleUpdate();

	return true;
}

void CMainMenu::initInput()
{
	m_pInput = new InputManager(this);
	m_pStartGame = m_pInput->createKeyboardAction(EventKeyboard::KeyCode::KEY_SPACE, "Spiel Starten");
	m_pToggleUI = m_pInput->createKeyboardAction(EventKeyboard::KeyCode::KEY_T, "UI de-/aktivieren");
	m_pReloadUI = m_pInput->createKeyboardAction(EventKeyboard::KeyCode::KEY_R, "UI neuladen");
}

void CMainMenu::update(float _dt)
{
	UPDATEUI;
	this->runAction(MoveBy::create(0.0f, Point(_dt * 10.0f, 0.0f)));
	m_pInput->update();
	
	if (m_pStartGame->wasReleased())
		startCallback(this);
}

void CMainMenu::startCallback(Object* sender)
{
	Director::getInstance()->replaceScene(HelloWorld::createScene());
}

void CMainMenu::exitCallback(Object* sender)
{
	Director::getInstance()->end();
}