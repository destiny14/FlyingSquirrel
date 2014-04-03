#include "MainMenu.h"
#include "CommonMain.h"
#include "Logfile.h"
#include "HelloWorldScene.h"
#include "LevelTestScene.h"
#include "UI.h"
#include "LevelEditor.h"
#include "StoryScene.h"

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

	Size visibleSize = Director::getInstance()->getVisibleSize();

	loadScene = false;
	t = 0.0f;

	initInput();
	ACTIVATEMAINMENUUI(this);

	m_pBackgroundSprite = Sprite::create("Resources/pictures/backgrounds/baum.png");
	m_pBackgroundSprite->setPosition(visibleSize.width * 0.5f, visibleSize.height * 0.5f);
	addChild(m_pBackgroundSprite);
	this->scheduleUpdate();

	return true;
}

void CMainMenu::initInput()
{
	m_pInput = new InputManager(this);
	EventKeyboard::KeyCode codes[] = { EventKeyboard::KeyCode::KEY_KP_ENTER, EventKeyboard::KeyCode::KEY_SPACE, EventKeyboard::KeyCode::KEY_0 };
	m_pStartGame = m_pInput->createKeyboardAction(codes, 3, "Spiel Starten");
}
    
void CMainMenu::update(float _dt)
{
	UPDATEUI(_dt);
	m_pInput->update();

	if (loadScene)
	{
		t += _dt;
		if (t >= 0.5f)
		{
			//Director::getInstance()->replaceScene(LevelTestScene::createScene());
			Director::getInstance()->replaceScene(StoryScene::createStoryScene());
		}
	}
		
	if (m_pStartGame->wasReleased())
		startCallback(this);
}

void CMainMenu::startCallback(Object* sender)
{
	DEACTIVATEUI;
	Size visibleSize = EGLView::getInstance()->getVisibleSize();
	visibleSize = Director::getInstance()->getVisibleSize();
	auto label = LabelTTF::create("Lade...", "Resources/fonts/Comic Book.ttf", 48);
	label->setPosition(visibleSize.width * 0.5f, visibleSize.height * 0.5f);
	this->addChild(label);
	loadScene = true;
}

void CMainMenu::exitCallback(Object* sender)
{
	Director::getInstance()->end();
}

void CMainMenu::levelEditorCallback(Object* sender)
{
	Director::getInstance()->replaceScene(LevelEditor::createScene(g_pCommonMain->getEditFilename()));
}