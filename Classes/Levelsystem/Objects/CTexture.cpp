#include "Texture.h"

USING_NS_CC;

Texture* Texture::create(char* filename)
{
	Texture* tex = new Texture();
	Sprite* sprite = Sprite::create(filename);
	if (sprite)
	{
		tex->setSprite(sprite);
		//tex->autorelease();
		return tex;
	}
	return nullptr;
}

// Texture (char*, float, float)
//
// erstellt eine neue textur aus einer bilddatei und einer position
Texture::Texture()
{

}

Texture::~Texture()
{

}

void Texture::setPosition(const Point& pos)
{
	Node::setPosition(pos);
	m_sprite->setPosition(pos);
}

void Texture::setPosition(float x, float y)
{
	Node::setPosition(x, y);
	m_sprite->setPosition(x, y);
}

// setSprite(Sprite*)
//
// setzt das sprite der textur
bool Texture::setSprite(Sprite* sprite)
{
	if (sprite)
	{
		m_sprite = sprite;
		return true;
	}
	else
	{
		m_sprite = nullptr;
		return false;
	}
}

// getSprite()
//
// gibt das Sprite der textur zurueck
Sprite* Texture::getSprite()
{
	return m_sprite;
}