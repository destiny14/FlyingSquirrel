#include "cocos2d.h"
#include "MainLayer.h"

MainLayer::MainLayer() {}

MainLayer::~MainLayer() {}

void MainLayer::setPhysicsObjects(list<Ground*> physicObjects)
{
	m_physicObjects = physicObjects;
}

list<Ground*> MainLayer::getPhysicsObjects()
{
	return m_physicObjects;
}