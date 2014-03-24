#include "Collider.h"
#include "PhysicsObject.h"

void AABBCollider::update()
{
	//PhysicsObject* obj = getPhysicsObject();
	//if (obj == nullptr) return;

	//m_bounds.origin = obj->getPosition();
}

void AABBCollider::debugDraw()
{
	PhysicsObject* obj = getPhysicsObject();
	if (obj == nullptr) return;

	Rect rect = getBoundingRect();
	rect.origin += obj->getPosition() - Point(rect.size.width, rect.size.height) * 0.5f;;

	DrawPrimitives::drawRect(rect.origin,
		Point(rect.origin.x + rect.size.width, rect.origin.y + rect.size.width));
}