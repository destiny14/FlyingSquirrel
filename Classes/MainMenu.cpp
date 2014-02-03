#include "MainMenu.h"
#include "CommonMain.h"
#include "Logfile.h"
#include "HelloWorldScene.h"

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
	if ( !Layer::init() )
    {
        return false;
    }
	
	Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
	origin.x += 3.0f;

	auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
										   CC_CALLBACK_1(CMainMenu::exitCallback, this));
	closeItem->setPosition(Point(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

	auto startItem = MenuItemFont::create("Start (Leertaste)", CC_CALLBACK_1(CMainMenu::startCallback, this));
	startItem->setPosition(Point(
		origin.x + visibleSize.width * 0.5f - closeItem->getContentSize().width * 0.5f,
		origin.y + visibleSize.height * 0.5f - closeItem->getContentSize().height * 0.5f));

	auto menu = Menu::create(closeItem, startItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1);
	
	char labelVerTxt[30];
	sprintf(labelVerTxt, "%s%s", g_pCommonMain->getAppVersion(), g_pCommonMain->getAppDebug() ? " Dev_Version" : "");
	auto labelVer = LabelTTF::create(labelVerTxt, "Arial", 12);
	labelVer->setPosition(Point(origin.x + labelVer->getContentSize().width * 0.5f,
							origin.y + visibleSize.height - labelVer->getContentSize().height));
	this->addChild(labelVer, 1);

	initInput();

	this->schedule(schedule_selector(CMainMenu::update));

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