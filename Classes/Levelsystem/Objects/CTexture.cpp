#include "cocos2d.h"
#include "Texture.h"

USING_NS_CC;

Texture::Texture(char* textureName, Rect position)
{
	m_sprite = Sprite::create(textureName, position);
}

Texture::~Texture()
{

}

void Texture::setSprite(Sprite* sprite)
{
	m_sprite = sprite;
}

Sprite* Texture::getSprite()
{
	return m_sprite;
}

Rect Texture::getBoundingBox()
{
	Rect t = Rect(m_sprite->getPositionX() - m_sprite->getContentSize().width * 0.5f,
		          m_sprite->getPositionY() - m_sprite->getContentSize().height * 0.5f,
		          m_sprite->getContentSize().width,
		          m_sprite->getContentSize().height);
	return t;
}