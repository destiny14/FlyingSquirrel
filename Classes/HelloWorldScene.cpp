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

	/*auto tex = Texture::create("ground.png");
	*/

	m_pInput = new InputManager(this);
	EventKeyboard::KeyCode code = EventKeyboard::KeyCode::KEY_0;
	m_pLSD = m_pInput->createKeyboardAction(&code, 1, "LSD");
	m_ground = Ground::create("ground.png");
	m_ground->setPosition(visibleSize.width * 0.5f, 100);
	/*Collider* comCollider = Collider::create(m_ground->getSprite()->getBoundingBox().size.width, m_ground->getSprite()->getBoundingBox().size.height);
	comCollider->setName("collider");
	m_ground->addComponent(comCollider);*/
	this->addChild(m_ground->getSprite(), 1);
	m_ground->getSprite()->setVisible(false);
	list<Ground*>* g = new list<Ground*>();
	g = this->getPhysicsObjects();
	g->push_back(m_ground);
	this->setPhysicsObjects(g);
	m_moveable = Player::create("sawyerstand.png", dynamic_cast<MainLayer*>(this), m_pInput);
	m_moveable->setPosition(visibleSize.width * 0.5f, 500);
	this->addChild(m_moveable->getSprite(), 1);

	this->getActionManager()->addAction(Follow::create(m_moveable->getSprite()), this, false);
	
	// m_ground->getSprite()->setVisible(false);
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Point(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1);

	/*auto sprite = Sprite::create("miep/*");
	sprite->setPosition()*/

	// ground box creation
	

	/////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    auto lblText = "Hello World";

    if (g_pCommonMain->getAppDebug())
    {
        lblText = "Hello World (DEBUG)";
    }

    auto label = LabelTTF::create(lblText, "Arial", 24);
    
    // position the label on the center of the screen
    label->setPosition(Point(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);
	Level* l = Level::createFromFile("test.xml");
	this->scheduleUpdate();
	//this->schedule(schedule_selector(HelloWorld::tick));
    g_pLogfile->fWrite(GREEN, false, "%s\n", "init succeeded");

	ACTIVATEINGAMEUI(this);

	ParallaxLayer* para = ParallaxLayer::create();
	Point pos = Point(2500.0f, 2100.0f);
	para->addParallaxElement(Sprite::create("bg1.png"), pos, Point(0.6f, 0.1f), 4);
	para->addParallaxElement(Sprite::create("bg2.png"), pos, Point(0.3f, 0.05f), 3);
	para->addParallaxElement(Sprite::create("bg3.png"), pos, Point(0.07f, 0.01f), 2);
	para->addParallaxElement(Sprite::create("bg4.png"), pos, Point(0.0f, 0.0f), 1);
	this->addChild(para);

    return true;
}

void HelloWorld::update(float dt)
{
	UPDATEUI;
	Node::update(dt);
	m_moveable->update(dt);
	m_pInput->update();

	if (m_pLSD->wasPressed())
		m_lsd = !m_lsd;

	if (m_lsd)
	{
		kmGLMatrixMode(KM_GL_MODELVIEW);
		kmGLTranslatef(400.0f, 300.0f, 0.0f);
		kmGLRotatef(45.0f * dt, -1.0f, 1.0f, 1.0f);
		m_rot += 45.0f * dt;
		kmGLTranslatef(-400.0f, -300.0f, 0.0f);
	}
	else if (m_rot != 0.0f)
	{
		kmGLMatrixMode(KM_GL_MODELVIEW);
		kmGLTranslatef(400.0f, 300.0f, 0.0f);
		kmGLRotatef(-m_rot, -1.0f, 1.0f, 1.0f);
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
