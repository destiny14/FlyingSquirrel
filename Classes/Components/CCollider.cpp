#include "Collider.h"

Collider* Collider::create(float width, float height)
{
	Collider* col = new Collider(width, height);
	if (col)
	{
		col->setName("collider");
		col->autorelease();
		return col;
	}
	CC_SAFE_DELETE(col);
	return nullptr;
}

Collider::Collider(float width, float height)
{
	m_collisionRectangle = Rect(0, 0, width, height);
}

Collider::~Collider() {}

Rect Collider::getCollisionRectangle()
{
	return m_collisionRectangle;
}

void Collider::setCollisionRectangle(Rect colRect)
{
	m_collisionRectangle = colRect;
}

bool Collider::init()
{
	return true;
}

void Collider::onEnter()
{
	Point r = getOwner()->getPosition();
	m_collisionRectangle.origin.x = r.x - (0.5 * m_collisionRectangle.size.width);
	m_collisionRectangle.origin.y = r.y - (0.5 * m_collisionRectangle.size.height);
}

void Collider::onExit()
{

}

void Collider::update(float dt)
{
	Point r = getOwner()->getPosition();
	m_collisionRectangle.origin.x = r.x - (0.5 * m_collisionRectangle.size.width);
	m_collisionRectangle.origin.y = r.y - (0.5 * m_collisionRectangle.size.height);
}

bool Collider::serialize(void* r)
{
	return true;
}