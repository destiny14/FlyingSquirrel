#include "cocos2d.h"
#include "Ground.h"
#include "Box2D\Box2D.h"
#include "Texture.h"
#include "..\Components\Collider.h"

USING_NS_CC;

Ground* Ground::create(char* filename)
{
	Ground* ground = new Ground();
	Texture* tex = Texture::create(filename);
	if (tex)
	{
		ground->setTexture(tex);
		ground->setCollider();
		ground->setGround(true);
		return ground;
	}
	return nullptr;
}

// Ground (Texture*)
// 
// erstellt eine neue Ground-Box mit der uebergebenen Textur
Ground::Ground()
{
	
}

Ground::~Ground()
{

}

void Ground::setCollider()
{
	setCollider(getSprite()->getBoundingBox().size.width, getSprite()->getBoundingBox().size.height);
}

void Ground::setCollider(float width, float height)
{
	Collider* collider = Collider::create(width, height);
	this->addComponent(collider);
}

Collider* Ground::getColliderComponent()
{
	return dynamic_cast<Collider*>(this->getComponent("collider"));
}

void Ground::setPosition(const Point& pos)
{
	Node::setPosition(pos);
	m_texture->setPosition(pos);
	Collider* col = getColliderComponent();
	if (col != nullptr)
		col->update(0.0f);
}

void Ground::setPosition(float x, float y)
{
	Node::setPosition(x, y);
	m_texture->setPosition(x, y);
	Collider* col = getColliderComponent();
	if (col != nullptr)
		col->update(0.0f);
}

Sprite* Ground::getSprite()
{
	return m_texture->getSprite();
}

// setTexture (Texture*)
//
// setzt die textur des objektes. die physikdefinitionen bleiben unveraendert
void Ground::setTexture(Texture* texture)
{
	m_texture = texture;
}

// getTexture()
//
// gibt einen zeiger auf die aktuelle textur zurück
Texture* Ground::getTexture()
{
	return m_texture;
}

void Ground::setGround(bool ground)
{
	m_isGround = true;
}

bool Ground::getGround()
{
	return m_isGround;
}