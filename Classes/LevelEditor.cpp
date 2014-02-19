#include "LevelEditor.h"
#include "UI.h"
#include "Levelsystem\Objects\Texture.h"
#include "InputManager.h"
#include "Levelsystem\Objects\Ground.h"
#include <math.h>

Scene* LevelEditor::createScene()
{
	auto scene = Scene::create();

	auto layer = LevelEditor::create();

	scene->addChild(layer);
	return scene;
}

LevelEditor::LevelEditor() {}
LevelEditor::~LevelEditor() {}

bool LevelEditor::init()
{
	m_pLevel = Level::createNew("tmpname.xml");
	MainLayer* mainL = MainLayer::create();
	mainL->retain();
	m_pLevel->setMainLayer(mainL);
	ChooseFileMenu = nullptr;
	m_pCurrentMoving = nullptr;
	m_pInput = new InputManager(this);
	m_mouseInputAction = m_pInput->createMouseAction("mousepos");
	m_visibleSize = Director::getInstance()->getVisibleSize();
	ACTIVATELEVELEDITORUI(this);
	m_pBackgroundSprite = nullptr;
	if (!Layer::init())
		return false;
	m_pBackgroundSprite = Sprite::create("ui_background.png");
	if (m_pBackgroundSprite != nullptr)
	{
		m_pBackgroundSprite->setPosition(0, m_visibleSize.height);
		m_pBackgroundSprite->setScale(500, m_visibleSize.height * 4);
		m_pBackgroundSprite->setZOrder(0);
		this->addChild(m_pBackgroundSprite);
	}
	this->scheduleUpdate();
	return true;
}

void LevelEditor::addTextureObjectCallback(Object* sender)
{
	ACTIVATEFILECHOOSERMENU(this, 0);
}

void LevelEditor::addGroundObjectCallback(Object* sender)
{
	ACTIVATEFILECHOOSERMENU(this, 1);
}

void LevelEditor::moveFileSelectUpCallback()
{
	if (ChooseFileMenu != nullptr)
		ChooseFileMenu->setPositionY(ChooseFileMenu->getPositionY() - 30);
}

void LevelEditor::moveFileSelectDownCallback()
{
	if (ChooseFileMenu != nullptr)
		ChooseFileMenu->setPositionY(ChooseFileMenu->getPositionY() + 30);
}

void LevelEditor::changeLayerCallback()
{
	MenuItemFont* mainMenuLayerLabel = (MenuItemFont*)MainMenu->getChildByTag(111);
	if (mainMenuLayerLabel != nullptr)
	{
		mainMenuLayerLabel->setString("NÄÄCHSTER");
	}
}

void LevelEditor::update(float dt)
{
	m_pInput->update();
	if (m_pCurrentMoving != nullptr)
	{
		Point p = m_mouseInputAction->getMousePosition();
		Point o = this->getPosition();
		float xp = ((int)((p.x - o.x) / 10)) * 10;
		float yp = ((int)((p.y - o.y) / 10)) * 10;
		m_pCurrentMoving->setPosition(
			xp,
			yp);
	}

	if (m_mouseInputAction->isMouse1Pressed())
	{
		if (m_pCurrentMoving != nullptr)
		{
			m_pCurrentMoving = nullptr;
		}
		else
		{
			Point mPos = m_mouseInputAction->getMousePosition();
			Point diff = (m_lastMousePos - mPos) * 35.0f * dt;
			m_lastMousePos = mPos;

			this->setPositionX(this->getPositionX() - diff.x);
			this->setPositionY(this->getPositionY() - diff.y);
		}
	}
	else
	{
		m_lastMousePos = m_mouseInputAction->getMousePosition();
	}
	UPDATEUI;
}

void LevelEditor::draw()
{
	//DrawPrimitives::drawSolidRect(Point(0, m_visibleSize.height), Point(120, 0), Color4F(0, 0, 255, 255));
}

void LevelEditor::chooseFileCallback(Object* sender, string s, int levelType)
{
	log("%i", levelType);
	if (levelType == 0)
	{
		auto tex = Texture::create(const_cast<char*>(s.c_str()));
		tex->retain();
		tex->setPosition(m_mouseInputAction->getMousePosition().x, m_mouseInputAction->getMousePosition().y);
		tex->getSprite()->setZOrder(-1);
		m_pCurrentMoving = tex;
		m_pLevel->getMainLayer()->getTextures()->push_back(tex);
		addChild(tex->getSprite());
	}
	else
	{
		log("%s", "ground created");
		auto ground = Ground::create(const_cast<char*>(s.c_str()));
		ground->setPosition(m_mouseInputAction->getMousePosition().x, m_mouseInputAction->getMousePosition().y);
		ground->retain();
		ground->getSprite()->setZOrder(-1);
		m_pCurrentMoving = ground;
		m_pLevel->getMainLayer()->getPhysicsObjects()->push_back(ground);
		addChild(ground->getSprite());
	}
	ChooseFileMenu->removeFromParentAndCleanup(true);
	ChooseFileNavMenu->removeFromParentAndCleanup(true);
}

void LevelEditor::saveLevelCallback()
{
	m_pLevel->SaveLevel();
}