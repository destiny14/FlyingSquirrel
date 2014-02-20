#include "LevelEditor.h"
#include "UI.h"
#include "Levelsystem\Objects\Texture.h"
#include "InputManager.h"
#include "Levelsystem\Objects\Ground.h"
#include <math.h>

Scene* LevelEditor::createScene(char* filename)
{
	auto scene = Scene::create();
	auto layer = LevelEditor::create(filename);
	scene->addChild(layer);
	return scene;
}

LevelEditor* LevelEditor::create(char* filename)
{
	LevelEditor* levelEditor = new LevelEditor();
	if (levelEditor && levelEditor->init(filename))
	{
		levelEditor->autorelease();
		return levelEditor;
	}
	else
	{
		delete levelEditor;
		levelEditor = NULL;
		return NULL;
	}
}

LevelEditor::LevelEditor() {}
LevelEditor::~LevelEditor() {}

bool LevelEditor::init(char* filename)
{

	if (!Layer::init())
		return false;
	m_snapToGrid = true;
	m_selectionMode = true;
	MainLayer* mainL = MainLayer::create();
	if (filename != "")
	{
		m_pLevel = Level::createFromFile(filename);
		mainL = m_pLevel->getMainLayer();
	}
	else
	{
		m_pLevel = Level::createNew("tmpname.xml");
	}
	mainL->retain();
	m_pLevel->setMainLayer(mainL);
	m_PlayerSpawner = Sprite::create("player_spawn.png");
	m_PlayerSpawner->retain();
	m_PlayerSpawner->setPosition(mainL->getPlayerSpawner()->getSpawnPosition());
	m_PlayerSpawner->setZOrder(1000);
	addChild(m_PlayerSpawner);
	ChooseFileMenu = nullptr;
	m_pCurrentMoving = nullptr;
	m_currentSelected = nullptr;
	m_currentSelectedGround = nullptr;
	m_pInput = new InputManager(this);
	m_mouseInputAction = m_pInput->createMouseAction("mousepos", 0);
	m_mouseInputAction2 = m_pInput->createMouseAction("mousepos", 1);
	EventKeyboard::KeyCode keysDelete[] = { EventKeyboard::KeyCode::KEY_DELETE };
	m_deleteObjectInputAction = m_pInput->createKeyboardAction(keysDelete, 1, "deleteObject");
	m_visibleSize = Director::getInstance()->getVisibleSize();
	ACTIVATELEVELEDITORUI(this);
	m_pBackgroundSprite = nullptr;
	int zOrder = -4;
	for (Texture* tex : *mainL->getTextures())
	{
		tex->setZOrder(zOrder);
		addChild(tex->getSprite());
		++zOrder;
	}
	zOrder = 1;
	for (Ground* g : *mainL->getPhysicsObjects())
	{
		g->setZOrder(zOrder);
		addChild(g->getSprite());
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
		mainMenuLayerLabel->setString("NYI...");
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

void LevelEditor::toggleSelectionMode()
{
	MenuItemFont* toggleSelectionModeLabel = (MenuItemFont*) MainMenu->getChildByTag(113);
	if (toggleSelectionModeLabel != nullptr)
	{
		if (m_selectionMode)
		{
			toggleSelectionModeLabel->setString("no selection");
			m_selectionMode = false;
		}
		else
		{
			toggleSelectionModeLabel->setString("selection");
			m_selectionMode = true;
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

	if (m_mouseInputAction->wasPressed())
	{
		if (m_pCurrentMoving != nullptr)
		{
			m_pCurrentMoving = nullptr;
			m_currentSelected = nullptr;
			m_currentSelectedGround = nullptr;
		}
		else if (m_currentSelected != nullptr)
		{
			Point o = this->getPosition();
			Point p = m_mouseInputAction->getMousePosition();
			if (m_currentSelected->getSprite()->getBoundingBox().containsPoint(Point(p - o)))
			{
				m_pCurrentMoving = m_currentSelected;
			}
		}
		else if (m_currentSelectedGround != nullptr)
		{
			Point o = this->getPosition();
			Point p = m_mouseInputAction->getMousePosition();
			if (m_currentSelectedGround->getSprite()->getBoundingBox().containsPoint(Point(p - o)))
			{
				m_pCurrentMoving = m_currentSelectedGround;
			}
		}
		else if (m_selectionMode)
		{
			m_currentSelected = nullptr;
			m_currentSelectedGround = nullptr;
			Point o = this->getPosition();
			Point p = m_mouseInputAction->getMousePosition();
			for (Texture* tex : *m_pLevel->getMainLayer()->getTextures())
			{ 
				if (tex->getSprite()->getBoundingBox().containsPoint(Point(p - o)))
				{
					if (m_currentSelected != nullptr)
					{
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
			for (Ground* ground : *m_pLevel->getMainLayer()->getPhysicsObjects())
			{
				if (ground->getSprite()->getBoundingBox().containsPoint(Point(p - o)))
				{
					if (m_currentSelectedGround != nullptr)
					{
						if (ground->getZOrder() > m_currentSelectedGround->getZOrder())
						{
							m_currentSelectedGround = ground;
						}
					}
					else
					{
						m_currentSelectedGround = ground;
					}
				}
			}
			/*m_pCurrentMoving = m_currentSelected;
			if (m_currentSelectedGround != nullptr)
				m_pCurrentMoving = m_currentSelectedGround;*/
		}
	}
	else if (m_mouseInputAction2->wasPressed())
	{
		m_lastMousePos = m_mouseInputAction->getMousePosition();
	}
	else if (m_mouseInputAction2->isPressed())
	{
		Point mPos = m_mouseInputAction->getMousePosition();
		Point diff = (m_lastMousePos - mPos) * 35.0f * dt;
		m_lastMousePos = mPos;

		this->setPositionX(this->getPositionX() - diff.x);
		this->setPositionY(this->getPositionY() - diff.y);
	}
	if (m_deleteObjectInputAction->isPressed())
	{
		if (m_currentSelected != nullptr)
		{
			removeChild(m_currentSelected->getSprite());
			m_pLevel->getMainLayer()->getTextures()->remove(m_currentSelected);
			//delete m_currentSelected;
			m_currentSelected = nullptr;
		}
		else if (m_currentSelectedGround != nullptr)
		{
			removeChild(m_currentSelectedGround->getSprite());
			m_pLevel->getMainLayer()->getPhysicsObjects()->remove(m_currentSelectedGround);
			//delete m_currentSelectedGround;
			m_currentSelectedGround = nullptr;
		}
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
		tex->getSprite()->setZOrder(1);
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
		ground->getSprite()->setZOrder(1);
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