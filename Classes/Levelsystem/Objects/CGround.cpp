#include "cocos2d.h"
#include "Ground.h"
#include "Box2D\Box2D.h"
#include "Texture.h"

USING_NS_CC;

Ground::Ground(Texture* texture, Rect location, const b2Vec2* vertices, int vertexCount)
{
	m_texture = texture;
	m_bodyDef.position.Set(location.origin.x + location.size.width * 0.5f, location.origin.y + location.size.height * 0.5f);
	b2PolygonShape shape;
	shape.Set(vertices, vertexCount);
	m_fixtureDef.shape = &shape;
}

Ground::~Ground()
{

}

void Ground::init(b2World* world)
{
	m_body = world->CreateBody(&m_bodyDef);
	m_body->CreateFixture(&m_fixtureDef);
}

void Ground::draw()
{

}

void Ground::setTexture(Texture* texture)
{
	m_texture = texture;
}

Texture* Ground::getTexture()
{
	return m_texture;
}

void Ground::setSprite(Sprite* sprite)
{
	m_sprite = sprite;
}

Sprite* Ground::getSprite()
{
	return m_sprite;
}