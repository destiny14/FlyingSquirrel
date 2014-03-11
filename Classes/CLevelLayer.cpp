#include "LevelLayer.h"

LevelLayer::LevelLayer() 
{
	m_textures = nullptr;
}

LevelLayer::~LevelLayer() {}

void LevelLayer::setTextures(list<Texture*>* textures)
{
	m_textures = textures;
}

list<Texture*>* LevelLayer::getTextures()
{
	if (m_textures == nullptr)
		m_textures = new list<Texture*>();
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

bool LevelLayer::init() 
{
	if (!Layer::init())
	{
		return false;
	}
	
	return true;
}
void LevelLayer::update(float dt) {}
void LevelLayer::draw() {}