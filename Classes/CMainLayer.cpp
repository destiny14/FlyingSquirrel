#include "MainLayer.h"

#include "Player.h"
#include "GameCamera.h"
#include "CommonMain.h"
#include "Aircurrent.h"
#include "UI.h"
#include "InputManager.h"
#include "ParallaxLayer.h"
#include "Mantis.h"
#include "SlimeHeap.h"
#include "Snail.h"

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
		Size visibleSize = Director::getInstance()->getVisibleSize();
		mainLayer->physic = new PhysicsEngine();
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

	//setPlayerSpawner(new PlayerSpawner(Point(visibleSize.width * 0.5f, 600)));
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
	m_pPlayer= Player::create(physic, "sawyer.png", dynamic_cast<MainLayer*>(this), m_pInput);
	m_pPlayer->setPosition(getPlayerSpawner()->getSpawnPosition());
	//m_pPlayer->getSprite()->setVisible(false);
	this->addChild(m_pPlayer->getSprite(), 5);
	//############################################################
	//## Init Camera                                            ##
	//############################################################
	m_pCam = new GameCamera(this);
	m_pCam->setFollowTarget(m_pPlayer);
	m_pCam->setBoundingRect(Rect(-2050.0f, -100.0f, 5505.0f, 6000.0f));
	//############################################################
	//## Init Level                                             ##
	//############################################################

	ParallaxLayer* para = ParallaxLayer::create();
	Point paraPos = Point(0, 0);
	//para->addParallaxElement(Sprite::create("bk5.png"), paraPos, Point(1,1), 5);
	para->addParallaxElement(Sprite::create("bk4.png"), paraPos, Point(0.3f, 0.1f), 4);
	para->addParallaxElement(Sprite::create("bk3.png"), paraPos, Point(0.1f, 0.07f), 3);
	para->addParallaxElement(Sprite::create("bk2.png"), paraPos, Point(0.08f, 0.007f), 2);
	para->addParallaxElement(Sprite::create("bk1.png"), paraPos, Point(0.0003f, 0.0001f), 1);
	this->addChild(para, -9999);

	for (Texture* t : *getTextures())
	{
		addChild(t->getSprite(), 0);
	}
	for (Ground* g : *getPhysicsObjects())
	{
		addChild(g->getSprite(), 1);
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
	if (m_pPlayer->getHealth() > 0.0f)
	m_pCam->update(dt);
	UPDATEUI(dt);

	if (m_pLSD->wasPressed())
		m_pCam->toggleLSD();

	if (_test->wasPressed())
	{
		//Aircurrent* air = Aircurrent::create(this, Point(0.0f, 2700.0f), Size(150.0f, 450.0f));
		//air->setPosition(_test->getMousePosition());
		//this->addChild(air);
	}

	for (Ground* g : *getPhysicsObjects())
	{
		g->setColliderBounds(g->getSprite()->getBoundingBox().size.width, g->getSprite()->getBoundingBox().size.height);
		g->update(dt);
	}

}

void MainLayer::draw()
{
	physic->draw();
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