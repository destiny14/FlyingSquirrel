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
	ChooseFileMenu = nullptr;
	m_pCurrentMoving = nullptr;
	m_pInput = new InputManager(this);
	m_mouseInputAction = m_pInput->createMouseAction("mousepos");
	m_visibleSize = Director::getInstance()->getVisibleSize();
	ACTIVATELEVELEDITORUI(this);
	m_pBackgroundSprite = nullptr;
	if (!Layer::init())
		return false;
	m_pBackgroundSprite = Sprite::create("leveleditorbg.png");
	if (m_pBackgroundSprite != nullptr)
	{
		m_pBackgroundSprite->setPosition(0, m_visibleSize.height);
		m_pBackgroundSprite->setScaleX(40);
		m_pBackgroundSprite->setScaleY(500);
		m_pBackgroundSprite->setZOrder(0);
		this->addChild(m_pBackgroundSprite);
	}
	this->scheduleUpdate();
	return true;
}

void LevelEditor::addTextureObjectCallback(Object* sender)
{
	auto tex = Texture::create("ground.png");
	tex->setPosition(m_mouseInputAction->getMousePosition().x, m_mouseInputAction->getMousePosition().y);
	tex->retain();
	tex->getSprite()->setZOrder(-1);
	m_pCurrentMoving = tex;
	addChild(tex->getSprite());
}

void LevelEditor::addGroundObjectCallback(Object* sender)
{
	auto ground = Ground::create("tree_2_parallax.png");
	ground->setPosition(m_mouseInputAction->getMousePosition().x, m_mouseInputAction->getMousePosition().y);
	ground->retain();
	ground->getSprite()->setZOrder(-1);
	m_pCurrentMoving = ground;
	addChild(ground->getSprite());
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

void LevelEditor::update(float dt)
{
	UPDATEUI;
	m_pInput->update();
	if (m_pCurrentMoving != nullptr)
	{
		Point p = m_mouseInputAction->getMousePosition();
		float xp = ((int) (p.x / 10)) * 10;
		float yp = ((int) (p.y / 10)) * 10;
		m_pCurrentMoving->setPosition(
			xp,
			yp);
	}
		//m_pCurrentMoving->setPosition(m_mouseInputAction->getMousePosition());

	if (m_mouseInputAction->isMouse1Pressed())
	{
		m_pCurrentMoving = nullptr;
	}
}

void LevelEditor::draw()
{
	//DrawPrimitives::drawSolidRect(Point(0, m_visibleSize.height), Point(120, 0), Color4F(0, 0, 255, 255));
}

void LevelEditor::chooseFileCallback(Object* sender, string s)
{
	char* chr;
	chr = &s[0];
	log("%s", chr);

	auto tex = Texture::create(chr);
	tex->setPosition(m_mouseInputAction->getMousePosition().x, m_mouseInputAction->getMousePosition().y);
	tex->retain();
	tex->getSprite()->setZOrder(-1);
	m_pCurrentMoving = tex;
	addChild(tex->getSprite());

	ChooseFileMenu->removeFromParentAndCleanup(false);
}