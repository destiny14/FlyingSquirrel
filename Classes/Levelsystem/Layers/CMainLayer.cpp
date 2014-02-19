#include "cocos2d.h"
#include "MainLayer.h"
#include "Objects\Player.h"
#include "..\CommonMain.h"

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
	m_pInput = new InputManager(this);
	m_pPlayer= Player::create("sawyer.png", dynamic_cast<MainLayer*>(this), m_pInput);
	m_pPlayer->setPosition(visibleSize.width * 0.5f - 50, 600);
	//m_pPlayer->setAffectedByGravity(false);
	this->addChild(m_pPlayer->getSprite(), 1);

	for (Texture* t : *getTextures())
	{
		addChild(t->getSprite());
	}
	for (Ground* g : *getPhysicsObjects())
	{
		addChild(g->getSprite());
	}
	this->scheduleUpdate();
	return true;
}

void MainLayer::update(float dt)
{
	m_pPlayer->update(dt);
	m_pInput->update();
	/*for (Texture* t : *getTextures())
	{
		t->update(dt);
	}*/
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