#include "cocos2d.h"
#include "MainLayer.h"

MainLayer::MainLayer() 
{
	m_physicObjects = nullptr;
}

MainLayer::~MainLayer() {}

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