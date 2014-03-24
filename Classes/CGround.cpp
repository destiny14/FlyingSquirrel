#include "Ground.h"

USING_NS_CC;

Ground* Ground::create(PhysicsEngine* _pEn, char* filename)
{
	Ground* ground = new Ground(_pEn);
	Texture* tex = Texture::create(filename);
	if (tex)
	{
		tex->retain();
		ground->setTexture(tex);
		ground->autorelease();
		return ground;
	}
	return nullptr;
}

// Ground (Texture*)
// 
// erstellt eine neue Ground-Box mit der uebergebenen Textur
Ground::Ground(PhysicsEngine* _pEn) : PhysicsObject(_pEn)
{
	m_texture = nullptr;
	m_pCol = new AABBCollider();
	m_pCol->setPhysicsObject(this);
}

Ground::~Ground()
{
	delete m_pCol;
	if (m_texture != nullptr)
		m_texture->release();
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
	setColliderBounds(getSprite()->getBoundingBox().size.width, getSprite()->getBoundingBox().size.height);
	m_texture->retain();
}

void Ground::setColliderBounds(float width, float height)
{
	m_pCol->setBoundingRect(Rect(0.0f, 0.0f, width, height));
}

// getTexture()
//
// gibt einen zeiger auf die aktuelle textur zurück
Texture* Ground::getTexture()
{
	return m_texture;
}