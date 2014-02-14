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
	m_ground = Ground::create("ground.png");
	m_ground->setPosition(visibleSize.width * 0.5f, 100);
	/*Collider* comCollider = Collider::create(m_ground->getSprite()->getBoundingBox().size.width, m_ground->getSprite()->getBoundingBox().size.height);
	comCollider->setName("collider");
	m_ground->addComponent(comCollider);*/
	this->addChild(m_ground->getSprite(), 1);
	m_ground->getSprite()->setVisible(false);
	list<Ground*> g = this->getPhysicsObjects();
	g.push_back(m_ground);
	this->setPhysicsObjects(g);
	m_moveable = Player::create("sawyerstand.png", dynamic_cast<MainLayer*>(this), m_pInput);
	m_moveable->setPosition(visibleSize.width * 0.5f, 500);
	this->addChild(m_moveable->getSprite(), 1);

	
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

    return true;
}

void HelloWorld::update(float dt)
{
	UPDATEUI;
	Node::update(dt);
	m_moveable->update(dt);
	m_pInput->update();
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
