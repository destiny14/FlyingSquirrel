#include "cocos2d.h"
#include "Ground.h"
#include "Box2D\Box2D.h"
#include "Texture.h"

USING_NS_CC;

Ground* Ground::create(char* filename)
{
	Ground* ground = new Ground();
	Texture* tex = Texture::create(filename);
	if (tex)
	{
		ground->setTexture(tex);
		ground->setCollisionRectangle();
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

void Ground::setCollisionRectangle()
{
	setCollisionRectangle(getSprite()->getBoundingBox().size.width, getSprite()->getBoundingBox().size.height);
}

void Ground::setCollisionRectangle(float width, float height)
{
	Rect r = Rect(getSprite()->getBoundingBox().origin.x, getSprite()->getBoundingBox().origin.y, width, height);
	g_pLogfile->writeHeading("created collision rectangle", 3);
	g_pLogfile->fLog(L_DEBUG, "X: %f<br />Y: %f<br />width: %f<br />height: %f<br />", r.origin.x, r.origin.y, r.size.width, r.size.height);
	m_collisionRectangle = r;
}

Rect Ground::getCollisionRectangle()
{
	float w = m_collisionRectangle.size.width;
	float h = m_collisionRectangle.size.height;
	Rect bb = m_texture->getSprite()->getBoundingBox();
	//g_pLogfile->writeHeading("created collision rectangle", 3);
	//g_pLogfile->fLog(L_DEBUG, "width: %f<br />height: %f<br />", w, h);
	//g_pLogfile->writeHeading("sprite stats", 3);
	//g_pLogfile->fLog(L_DEBUG, "X: %f<br />Y: %f<br />width: %f<br />height: %f<br />", getSprite()->getPositionX(), getSprite()->getPositionY(), getSprite()->getContentSize().width, getSprite()->getContentSize().height);
	Rect tmp = Rect(bb.origin.x, bb.origin.y, w, h);
	return tmp;
}

void Ground::setPosition(const Point& pos)
{
	Node::setPosition(pos);
	m_texture->setPosition(pos);
}

void Ground::setPosition(float x, float y)
{
	Node::setPosition(x, y);
	m_texture->setPosition(x, y);
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