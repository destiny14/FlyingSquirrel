#include "Collider.h"

void CompoundCollider::addCollider(Collider* _col)
{
	m_list.push_back(_col);
}

void CompoundCollider::remCollider(Collider* _col)
{
	m_list.remove(_col);
}

std::list<Collider*>* CompoundCollider::getColliders()
{
	return &m_list;
}

void CompoundCollider::update()
{
	for (Collider* col : m_list)
	{
		col->update();
	}
}

void CompoundCollider::setPhysicsObject(PhysicsObject* _obj)
{
	Collider::setPhysicsObject(_obj);
	for (Collider* col : m_list)
	{
		col->setPhysicsObject(_obj);
	}
}

void CompoundCollider::debugDraw()
{
	for (Collider* col : m_list)
	{
		col->debugDraw();
	}
}