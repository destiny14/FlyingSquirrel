#include "cocos2d.h"
#include "Ground.h"
#include "Box2D\Box2D.h"
#include "Texture.h"

USING_NS_CC;

// Ground (Texture*)
// 
// erstellt eine neue Ground-Box mit der uebergebenen Textur
Ground::Ground(Texture* texture)
{
	m_texture = texture;
	float posx = texture->getSprite()->getPositionX() / PTM_RATIO;
	float posy = texture->getSprite()->getPositionY() / PTM_RATIO;
	m_bodyDef.position.Set(posx, posy);
	m_polyShape.SetAsBox((texture->getSprite()->getContentSize().width /2) / PTM_RATIO, (texture->getSprite()->getContentSize().height / 2) / PTM_RATIO);
	m_fixtureDef.shape = &m_polyShape;
}

Ground::~Ground()
{

}

// init (b2World*)
//
// macht die box dem physiksystem bekannt. Ausgelagert um später waehrend der simulation objekte hinzufuegen zu koennen
void Ground::init(b2World* world)
{
	m_body = world->CreateBody(&m_bodyDef);
	m_body->CreateFixture(&m_fixtureDef);
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