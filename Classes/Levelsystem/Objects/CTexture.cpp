#include "cocos2d.h"
#include "Texture.h"

USING_NS_CC;

// Texture (char*, float, float)
//
// erstellt eine neue textur aus einer bilddatei und einer position
Texture::Texture(char* textureName, float xpos, float ypos)
{
	m_sprite = Sprite::create(textureName);
	m_sprite->setPosition(xpos, ypos);
}

Texture::~Texture()
{

}

// setSprite(Sprite*)
//
// setzt das sprite der textur
void Texture::setSprite(Sprite* sprite)
{
	m_sprite = sprite;
}

// getSprite()
//
// gibt das Sprite der textur zurueck
Sprite* Texture::getSprite()
{
	return m_sprite;
}

// getBoundingBox()
//
// nicht sicher ob benoetigt, bb des sprites liefert shit
Rect Texture::getBoundingBox()
{
	float x = m_sprite->getPositionX() - m_sprite->getContentSize().width * 0.5f;
	float y = m_sprite->getPositionY() - m_sprite->getContentSize().height * 0.5f;
	float width = m_sprite->getContentSize().width;
	float height = m_sprite->getContentSize().height;
	Rect t = Rect(x, y, height, width);
	return t;
}