#include "MainLayer.h"

#include "Objects\Player.h"
#include "..\GameCamera.h"
#include "..\CommonMain.h"
#include "..\Nut.h"
#include "..\UI.h"
#include "..\InputManager.h"

MainLayer::MainLayer() : LevelLayer()
{
	m_physicObjects = nullptr;
}

MainLayer::~MainLayer() {}

MainLayer* MainLayer::create()
{
	MainLayer* mainLayer = new MainLayer();
	if (mainLayer)
	{
		mainLayer->setName("mainLayer");
		mainLayer->autorelease();
		mainLayer->retain();
	}
	else
	{
		delete mainLayer;
		mainLayer = nullptr;
		return nullptr;
	}
	return mainLayer;
}

bool MainLayer::init()
{
	if (!LevelLayer::init())
		return false;

	Size visibleSize = Director::getInstance()->getVisibleSize();
	//############################################################
	//## Init Input                                             ##
	//############################################################
	m_pInput = new InputManager(this);
	_test = m_pInput->createMouseAction("TEST", 0);
	EventKeyboard::KeyCode code = EventKeyboard::KeyCode::KEY_0;
	m_pLSD = m_pInput->createKeyboardAction(&code, 1, "LSD");
	//############################################################
	//## Init Player                                            ##
	//############################################################
	m_pPlayer= Player::create("sawyer.png", dynamic_cast<MainLayer*>(this), m_pInput);
	m_pPlayer->setPosition(visibleSize.width * 0.5f - 50, 600);
	this->addChild(m_pPlayer->getSprite(), 1);
	//############################################################
	//## Init Camera                                            ##
	//############################################################
	m_pCam = new GameCamera(this);
	m_pCam->setFollowTarget(m_pPlayer);
	m_pCam->setBoundingRect(Rect(-10000.0f, -10000.0f, 20000.0f, 20000.0f));
	//############################################################
	//## Init Level                                             ##
	//############################################################
	for (Texture* t : *getTextures())
	{
		addChild(t->getSprite());
	}
	for (Ground* g : *getPhysicsObjects())
	{
		addChild(g->getSprite());
	}
	this->scheduleUpdate();

	ACTIVATEINGAMEUI(this);

	return true;
}

void MainLayer::update(float dt)
{
	dt = dt > (1.0f / 60.0f) ? (1.0f / 60.0f) : dt;
	m_pPlayer->update(dt);
	m_pInput->update();
	m_pCam->update(dt);
	UPDATEUI;

	if (m_pLSD->wasPressed())
		m_pCam->toggleLSD();

	if (_test->wasPressed())
	{
		CollectibleNut* nut = CollectibleNut::create(this);
		nut->setPosition(_test->getMousePosition() - this->getPosition());
		this->addChild(nut);
	}

	for (Ground* g : *getPhysicsObjects())
	{
		g->update(dt);
	}
}

void MainLayer::draw()
{
	if (g_pCommonMain->getAppDebug())
	{
		DrawPrimitives::drawRect(Point(
			m_pPlayer->getPlayerColliderComponent()->getBottomCollider().origin.x,
			m_pPlayer->getPlayerColliderComponent()->getBottomCollider().origin.y),
			Point(
			m_pPlayer->getPlayerColliderComponent()->getBottomCollider().origin.x + m_pPlayer->getPlayerColliderComponent()->getBottomCollider().size.width,
			m_pPlayer->getPlayerColliderComponent()->getBottomCollider().origin.y + m_pPlayer->getPlayerColliderComponent()->getBottomCollider().size.height));
		DrawPrimitives::drawRect(Point(
			m_pPlayer->getPlayerColliderComponent()->getTopCollider().origin.x,
			m_pPlayer->getPlayerColliderComponent()->getTopCollider().origin.y),
			Point(									
			m_pPlayer->getPlayerColliderComponent()->getTopCollider().origin.x + m_pPlayer->getPlayerColliderComponent()->getTopCollider().size.width,
			m_pPlayer->getPlayerColliderComponent()->getTopCollider().origin.y + m_pPlayer->getPlayerColliderComponent()->getTopCollider().size.height));
		DrawPrimitives::drawRect(Point(
			m_pPlayer->getPlayerColliderComponent()->getLeftCollider().origin.x,
			m_pPlayer->getPlayerColliderComponent()->getLeftCollider().origin.y),
			Point(
			m_pPlayer->getPlayerColliderComponent()->getLeftCollider().origin.x + m_pPlayer->getPlayerColliderComponent()->getLeftCollider().size.width,
			m_pPlayer->getPlayerColliderComponent()->getLeftCollider().origin.y + m_pPlayer->getPlayerColliderComponent()->getLeftCollider().size.height));

		DrawPrimitives::drawRect(Point(
			m_pPlayer->getPlayerColliderComponent()->getRightCollider().origin.x,
			m_pPlayer->getPlayerColliderComponent()->getRightCollider().origin.y),
			Point(
			m_pPlayer->getPlayerColliderComponent()->getRightCollider().origin.x + m_pPlayer->getPlayerColliderComponent()->getRightCollider().size.width,
			m_pPlayer->getPlayerColliderComponent()->getRightCollider().origin.y + m_pPlayer->getPlayerColliderComponent()->getRightCollider().size.height));
	}
}

void MainLayer::setPhysicsObjects(list<Ground*>* physicObjects)
{
	m_physicObjects = physicObjects;
}

list<Ground*>* MainLayer::getPhysicsObjects()
{
	if (m_physicObjects == nullptr)
	{
		m_physicObjects = new list<Ground*>();
	}
	return m_physicObjects;
}

void MainLayer::setPlayerSpawner(PlayerSpawner* pS)
{
	m_playerSpawner = pS;
}

PlayerSpawner* MainLayer::getPlayerSpawner()
{
	return m_playerSpawner;
}

void MainLayer::menuCloseCallback(Object* pSender)
{
	Director::getInstance()->end();
}