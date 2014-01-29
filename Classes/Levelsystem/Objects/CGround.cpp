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
}

Ground::~Ground()
{

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