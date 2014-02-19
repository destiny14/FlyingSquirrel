#include "CommonMain.h"
#include "HelloWorldScene.h"
#include "Logfile.h"
#include "TestLayer.h"
#include "Ground.h"
#include "Texture.h"
#include "Moveable.h"
#include "Levelsystem\Level.h"
#include "Levelsystem\Objects\Player.h"
#include "Components\Collider.h"
#include <list>
#include <iostream>
#include <queue>
#include "UI.h"
#include "Levelsystem\ParallaxLayer.h"

USING_NS_CC;

using namespace std;

Scene* HelloWorld::createScene()
{
	
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();
	auto layer2 = TestLayer::create();
    // add layer as a child to scene
    scene->addChild(layer);

	//scene->addChild(layer2);

    // return the scene
    return scene;
}

HelloWorld::HelloWorld()
{
	
	
}

HelloWorld::~HelloWorld()
{
    g_pLogfile->Del();
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	m_rot = 0.0f;
	m_lsd = false;
	
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

	// Logfile einrichten
	g_pLogfile->writeHeading("flying squirrel log", 1);

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

	m_pInput = new InputManager(this);
	EventKeyboard::KeyCode code = EventKeyboard::KeyCode::KEY_0;
	m_pLSD = m_pInput->createKeyboardAction(&code, 1, "LSD");
	m_ground = Ground::create("ground.png");
	m_ground->setPosition(visibleSize.width * 0.5f, 100);
	this->addChild(m_ground->getSprite(), 1);
	//m_ground->getSprite()->setVisible(false);
	list<Ground*>* g = new list<Ground*>();
	g = this->getPhysicsObjects();
	g->push_back(m_ground);
	this->setPhysicsObjects(g);
	m_moveable = Player::create("sawyer.png", dynamic_cast<MainLayer*>(this), m_pInput);
	m_moveable->setPosition(visibleSize.width * 0.5f, 500);
	this->addChild(m_moveable->getSprite(), 1);

	m_pCam = new GameCamera(this);
	m_pCam->setFollowTarget(m_moveable);
	m_pCam->setBoundingRect(Rect(-800.0f, -800.0f, 2400.0f, 2400.0f));

	ParallaxLayer* para = ParallaxLayer::create();
	Point paraPos = Point(2500.0f, 2000.0f);
	para->addParallaxElement(Sprite::create("bg1.png"), paraPos, Point(0.3f, 0.01f), 4);
	para->addParallaxElement(Sprite::create("bg2.png"), paraPos, Point(0.03f, 0.001f), 3);
	para->addParallaxElement(Sprite::create("bg3.png"), paraPos, Point(0.003f, 0.0001f), 2);
	para->addParallaxElement(Sprite::create("bg4.png"), paraPos, Point(0.0003f, 0.00001f), 1);
	this->addChild(para, -9999);

	//Level* l = Level::createFromFile("test.xml");
	this->scheduleUpdate();
	//this->schedule(schedule_selector(HelloWorld::tick));
    g_pLogfile->fWrite(GREEN, false, "%s\n", "init succeeded");

	ACTIVATEINGAMEUI(this);

    return true;
}

void HelloWorld::update(float dt)
{
	dt = dt > (1.0f / 60.0f)? (1.0f / 60.0f) : dt;
	Node::update(dt);
	m_moveable->update(dt);
	m_pInput->update();
	m_pCam->update(dt);
	UPDATEUI;

	if (m_pLSD->wasPressed())
		m_lsd = !m_lsd;

	if (m_lsd)
	{
		kmGLMatrixMode(KM_GL_MODELVIEW);
		kmGLTranslatef(400.0f, 300.0f, 0.0f);
		kmGLRotatef(45.0f * dt, 0.0f, 0.0f, 1.0f);
		m_rot += 45.0f * dt;
		kmGLTranslatef(-400.0f, -300.0f, 0.0f);
	}
	else if (m_rot != 0.0f)
	{
		kmGLMatrixMode(KM_GL_MODELVIEW);
		kmGLTranslatef(400.0f, 300.0f, 0.0f);
		kmGLRotatef(-m_rot, 0.0f, 0.0f, 1.0f);
		m_rot = 0.0f;
		kmGLTranslatef(-400.0f, -300.0f, 0.0f);
	}
}

void HelloWorld::draw()
{
	if (g_pCommonMain->getAppDebug())
	{
		DrawPrimitives::drawRect(Point(
			m_ground->getColliderComponent()->getCollisionRectangle().origin.x,
			m_ground->getColliderComponent()->getCollisionRectangle().origin.y),
			Point(
			m_ground->getColliderComponent()->getCollisionRectangle().origin.x + m_ground->getColliderComponent()->getCollisionRectangle().size.width,
			m_ground->getColliderComponent()->getCollisionRectangle().origin.y + m_ground->getColliderComponent()->getCollisionRectangle().size.height));

		DrawPrimitives::drawRect(Point(
			m_moveable->getPlayerColliderComponent()->getBottomCollider().origin.x,
			m_moveable->getPlayerColliderComponent()->getBottomCollider().origin.y),
			Point(
			m_moveable->getPlayerColliderComponent()->getBottomCollider().origin.x + m_moveable->getPlayerColliderComponent()->getBottomCollider().size.width,
			m_moveable->getPlayerColliderComponent()->getBottomCollider().origin.y + m_moveable->getPlayerColliderComponent()->getBottomCollider().size.height));

		DrawPrimitives::drawRect(Point(
			m_moveable->getPlayerColliderComponent()->getLeftCollider().origin.x,
			m_moveable->getPlayerColliderComponent()->getLeftCollider().origin.y),
			Point(
			m_moveable->getPlayerColliderComponent()->getLeftCollider().origin.x + m_moveable->getPlayerColliderComponent()->getLeftCollider().size.width,
			m_moveable->getPlayerColliderComponent()->getLeftCollider().origin.y + m_moveable->getPlayerColliderComponent()->getLeftCollider().size.height));

		DrawPrimitives::drawRect(Point(
			m_moveable->getPlayerColliderComponent()->getRightCollider().origin.x,
			m_moveable->getPlayerColliderComponent()->getRightCollider().origin.y),
			Point(
			m_moveable->getPlayerColliderComponent()->getRightCollider().origin.x + m_moveable->getPlayerColliderComponent()->getRightCollider().size.width,
			m_moveable->getPlayerColliderComponent()->getRightCollider().origin.y + m_moveable->getPlayerColliderComponent()->getRightCollider().size.height));
	}
}

void HelloWorld::menuCloseCallback(Object* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
