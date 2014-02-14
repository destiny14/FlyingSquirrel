#include "Texture.h"

USING_NS_CC;

Texture* Texture::create(char* filename)
{
	Texture* tex = new Texture();
	Sprite* sprite = Sprite::create(filename);
	if (sprite)
	{
		tex->setFilename(filename);
		tex->setSprite(sprite);
		tex->autorelease();
		return tex;
	}
	return nullptr;
}

// Texture (char*, float, float)
//
// erstellt eine neue textur aus einer bilddatei und einer position
Texture::Texture()
{
	m_sprite = nullptr;
}

Texture::~Texture()
{
	if (m_sprite != nullptr)
		m_sprite->release();
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
	if (m_sprite != nullptr)
		m_sprite->release();
	m_sprite = sprite;

	if (m_sprite)
		m_sprite->retain();

	return m_sprite != nullptr;
}

// getSprite()
//
// gibt das Sprite der textur zurueck
Sprite* Texture::getSprite()
{
	return m_sprite;
}

void Texture::setFilename(char* filename)
{
	m_filename = filename;
}

char* Texture::getFilename()
{
	return m_filename;
}