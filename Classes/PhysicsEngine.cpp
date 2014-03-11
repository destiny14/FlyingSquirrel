#include "PhysicsEngine.h"

void PhysicsEngine::addPhysicsObject(PhysicsObject* _obj)
{
	m_list.push_back(_obj);
}

void PhysicsEngine::removePhysicsObject(PhysicsObject* _obj)
{
	m_list.remove(_obj);
}

bool PhysicsEngine::checkForBlockingCollision(PhysicsObject* _obj)
{
	for (PhysicsObject* o : m_list)
	{
		if (o == _obj) continue;

		if (isCollision(_obj->getCollider(), o->getCollider()))
		{
			if (_obj->onCollision(o, _obj->getCollider()->getTag()))
				return true;
		}
	}

	return false;
}

bool PhysicsEngine::isCollision(Collider* _c1, Collider* _c2)
{
	switch (_c1->getColliderType())
	{
		case ColliderType::AABB:
			return isCollision(dynamic_cast<AABBCollider*>(_c1), _c2);
		case ColliderType::COMPOUND:
			return isCollision(dynamic_cast<CompoundCollider*>(_c1), _c2);
	}

	return false;
}

bool PhysicsEngine::isCollision(AABBCollider* _c1, Collider* _c2)
{
	switch (_c2->getColliderType())
	{
		case ColliderType::AABB:
			return isCollision(_c1, dynamic_cast<AABBCollider*>(_c2));
		case ColliderType::COMPOUND:
			return isCollision(_c1, dynamic_cast<CompoundCollider*>(_c2));
	}

	return false;
}

bool PhysicsEngine::isCollision(CompoundCollider* _c1, Collider* _c2)
{
	switch (_c2->getColliderType())
	{
	case ColliderType::AABB:
		return isCollision(_c1, dynamic_cast<AABBCollider*>(_c2));
	case ColliderType::COMPOUND:
		return isCollision(_c1, dynamic_cast<CompoundCollider*>(_c2));
	}

	return false;
}

bool PhysicsEngine::isCollision(AABBCollider* _c1, AABBCollider* _c2)
{
	Rect a = _c1->getBoundingRect();
	a.origin += _c1->getPhysicsObject()->getPosition();
	Rect b = _c2->getBoundingRect();
	b.origin += _c2->getPhysicsObject()->getPosition();
	return a.intersectsRect(b);
}

bool PhysicsEngine::isCollision(CompoundCollider* _c1, AABBCollider* _c2)
{
	for (Collider* _c3 : *_c1->getColliders())
	{
		if (isCollision(_c3, _c2))
		{
			_c1->setTag(_c3->getTag());
			return true;
		}
	}
	return false;
}

bool PhysicsEngine::isCollision(AABBCollider* _c1, CompoundCollider* _c2)
{
	return isCollision(_c2, _c1);
}

bool PhysicsEngine::isCollision(CompoundCollider* _c1, CompoundCollider* _c2)
{
	for (Collider* _c3 : *_c1->getColliders())
	{
		if (isCollision(_c3, _c2))
		{
			_c1->setTag(_c3->getTag());
			return true;
		}
	}
	return false;
}