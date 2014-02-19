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
	m_snapToGrid = true;
	m_pLevel = Level::createNew("tmpname.xml");
	MainLayer* mainL = MainLayer::create();
	mainL->retain();
	m_pLevel->setMainLayer(mainL);
	ChooseFileMenu = nullptr;
	m_pCurrentMoving = nullptr;
	m_currentSelected = nullptr;
	m_pInput = new InputManager(this);
	m_mouseInputAction = m_pInput->createMouseAction("mousepos");
	m_visibleSize = Director::getInstance()->getVisibleSize();
	ACTIVATELEVELEDITORUI(this);
	m_pBackgroundSprite = nullptr;
	if (!Layer::init())
		return false;
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
		mainMenuLayerLabel->setString("N��CHSTER");
	}
}

void LevelEditor::toggleGridCallback()
{
	MenuItemFont* toggleGridLabel = (MenuItemFont*) MainMenu->getChildByTag(112);
	if (toggleGridLabel != nullptr)
	{
		if (m_snapToGrid)
		{
			toggleGridLabel->setString("no snap");
			m_snapToGrid = false;
		}
		else
		{
			toggleGridLabel->setString("snap to grid");
			m_snapToGrid = true;
		}
		
	}
}

void LevelEditor::update(float dt)
{
	m_pInput->update();
	Point p = m_mouseInputAction->getMousePosition();
	if (m_pCurrentMoving != nullptr)
	{
		
		Point o = this->getPosition();
		if (m_snapToGrid)
		{
			float xp = ((int) ((p.x - o.x) / 10)) * 10;
			float yp = ((int) ((p.y - o.y) / 10)) * 10;
			m_pCurrentMoving->setPosition(
				xp,
				yp);
		}
		else
		{
			Point o = this->getPosition();
			m_pCurrentMoving->setPosition(p - o);
		}
	}

	if (m_mouseInputAction->isMouse1Pressed())
	{
		if (m_pCurrentMoving != nullptr)
		{
			m_pCurrentMoving = nullptr;
		}
		else
		{
			for (Texture* tex : *m_pLevel->getMainLayer()->getTextures())
			{
				Point o = this->getPosition();
				if (tex->getSprite()->getBoundingBox().containsPoint(m_mouseInputAction->getMousePosition()))
				{
					if (m_currentSelected != nullptr)
					{
						log("Z Order: %i, %i", tex->getZOrder() > m_currentSelected->getZOrder());
						if (tex->getZOrder() > m_currentSelected->getZOrder())
						{
							m_currentSelected = tex;
						}
					}
					else
					{
						m_currentSelected = tex;
					}
					
				}
			}
			m_pCurrentMoving = m_currentSelected;
		}
	}
	else if (m_mouseInputAction->isMouse2Pressed())
	{
		Point mPos = m_mouseInputAction->getMousePosition();
		Point diff = (m_lastMousePos - mPos) * 35.0f * dt;
		m_lastMousePos = mPos;

		this->setPositionX(this->getPositionX() - diff.x);
		this->setPositionY(this->getPositionY() - diff.y);
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