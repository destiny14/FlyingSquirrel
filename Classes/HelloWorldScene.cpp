#include "Box2D/Box2D.h"
#include "GLES-Render.h"
#include "CommonMain.h"
#include "HelloWorldScene.h"
#include "Logfile.h"
#include "TestLayer.h"
#include <iostream>

USING_NS_CC;

Scene* HelloWorld::createScene()
{
	
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

	auto layer2 = TestLayer::create();

    // add layer as a child to scene
    scene->addChild(layer);

	scene->addChild(layer2);

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
	g_pLogfile->WriteHeading("flying squirrel log", 1);
    g_pLogfile->fLog(L_DEBUG, "%s\n", "Debug Message");
    g_pLogfile->fLog(L_WARNING, "%s\n", "Warning");
    g_pLogfile->fLog(L_ERROR, "%s\n", "Error Message!");

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

	// Welt einrichten
	b2Vec2 gravity;
	gravity.Set(0.0f, 0.0f);
	m_world = new b2World(gravity);

	// Body & Fixture Definition Box
	b2BodyDef def;
	def.type = b2_dynamicBody;
	def.position.Set(200 / PTM_RATIO, 200 / PTM_RATIO);
	m_box = m_world->CreateBody(&def);

	b2PolygonShape boxShape;
	boxShape.SetAsBox(25 / PTM_RATIO, 25 / PTM_RATIO);

	b2FixtureDef fixDef;
	fixDef.shape = &boxShape;
	fixDef.density = 1.0f;
	fixDef.friction = 0.0;
	fixDef.restitution = 0.1f;
	m_box->CreateFixture(&fixDef);

	// Box2d Debugging.
	m_debugDraw = new GLESDebugDraw(PTM_RATIO);
	m_world->SetDebugDraw(m_debugDraw);

	// Enable debugging flags.
	uint32 flags = 0;
	flags += b2Draw::e_shapeBit;
	/*flags += b2Draw::e_jointBit;
	flags += b2Draw::e_aabbBit;
	flags += b2Draw::e_pairBit;
	flags += b2Draw::e_centerOfMassBit;*/
	m_debugDraw->SetFlags(flags);

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

	this->schedule(schedule_selector(HelloWorld::tick));
    g_pLogfile->fWrite(GREEN, false, "%s\n", "init succeeded");
    return true;
}

void HelloWorld::tick(float dt)
{
	// Physik simulieren
	m_world->Step(dt, 8, 4);
}

void HelloWorld::draw()
{
	// Physik Debug-Daten zeichnen
	m_world->DrawDebugData();
}

void HelloWorld::menuCloseCallback(Object* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
