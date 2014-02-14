#include "cocos2d.h"
#include "Moveable.h"
#include "LevelLayer.h"
#include "..\Components\Collider.h"
#include <list>

USING_NS_CC;
using namespace std;

Moveable* Moveable::create(char* filename, MainLayer* parent)
{
	Moveable* mov = new Moveable();
	Texture* tex = Texture::create(filename);
	if (tex)
	{
		mov->setTexture(tex);
		mov->setCollider();
		mov->setParent(parent);
		mov->setGround(false);
		return mov;
	}
	return nullptr;
}

Moveable::Moveable()
{
	m_grounded = false;
	m_gravity = -200.0f;
	m_velocity = 0.0f;
}

Moveable::~Moveable()
{

}

void Moveable::updateCollider() 
{
	/*Rect oldCollider = getCollider();
	setCollider(oldCollider.size.width, oldCollider.size.height);*/
}

void Moveable::setParent(MainLayer* parent)
{
	m_parent = parent;
}

MainLayer* Moveable::getParent()
{
	return m_parent;
}

void Moveable::setAffectedByGravity(bool affectedByGravity)
{
	m_affectedByGravity = affectedByGravity;
}

bool Moveable::getAffectedByGrafity()
{
	return m_affectedByGravity;
}

bool Moveable::getGrounded()
{
	return m_grounded;
}

void Moveable::setGrounded(bool g)
{
	m_grounded = g;
}

void Moveable::update(float dt, bool overwriteCollisionCheck)
{
	if (m_affectedByGravity)
	{
		if (!m_grounded)
		{
			float x = getPositionX();
			float y = getPositionY();
			y += m_velocity * dt;
			m_velocity += m_gravity * dt;
			setPositionY(y);
			updateCollider();
			if (!overwriteCollisionCheck)
				CheckForCollisions();
		}
	}
	Node::update(dt);
}

void Moveable::CheckForCollisions()
{
	list<Ground*>* physObj = m_parent->getPhysicsObjects();
	for (Ground* g : *physObj)
	{
		if (g->getGround() == true)
		{
			Collider* c = dynamic_cast<Collider*>(g->getComponent("collider"));
			Collider* c2 = getColliderComponent();
			if (c->getCollisionRectangle().intersectsRect(getColliderComponent()->getCollisionRectangle()))
			{
				// kollision
				m_grounded = true;
			}
		}
	}
}