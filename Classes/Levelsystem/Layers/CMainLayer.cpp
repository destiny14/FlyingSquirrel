#include "cocos2d.h"
#include "MainLayer.h"

MainLayer::MainLayer() 
{
	m_physicObjects = nullptr;
}

MainLayer::~MainLayer() {}

MainLayer* MainLayer::create()
{
	MainLayer* mainLayer = new MainLayer();
	if (mainLayer)
	{
		mainLayer->autorelease();
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
	
	for (Texture* t : *getTextures())
	{
		addChild(t->getSprite());
	}
	for (Ground* g : *getPhysicsObjects())
	{
		addChild(g->getSprite());
	}
	return true;
}

void MainLayer::update(float dt)
{
	for (Texture* t : *getTextures())
	{
		t->update(dt);
	}
}

void MainLayer::draw()
{

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