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

void LevelLayer::setName(char* name)
{
	m_name = name;
}

char* LevelLayer::getName()
{
	return m_name;
}