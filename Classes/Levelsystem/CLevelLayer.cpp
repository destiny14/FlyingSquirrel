#include "cocos2d.h"
#include "LevelLayer.h"

LevelLayer::LevelLayer() {}

LevelLayer::~LevelLayer() {}

void LevelLayer::setTextures(list<Texture*> textures)
{
	m_textures = textures;
}

list<Texture*> LevelLayer::getTextures()
{
	return m_textures;
}

void LevelLayer::setPhysicsObjects(list<Ground*> physicObjects)
{
	m_physicObjects = physicObjects;
}

list<Ground*> LevelLayer::getPhysicsObjects()
{
	return m_physicObjects;
}

void LevelLayer::setName(char* name)
{
	m_name = name;
}

char* LevelLayer::getName()
{
	return m_name;
}