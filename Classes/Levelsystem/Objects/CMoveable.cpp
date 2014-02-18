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
	m_gravity = -600.0f;
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

void Moveable::addVelocity(float _x, float _y)
{
	m_velocity.x += _x;
	m_velocity.y += _y;
}

void Moveable::setVelocityX(float _x)
{
	m_velocity.x = _x;
}

float Moveable::getVelocityX()
{
	return m_velocity.x;
}

void Moveable::update(float dt, bool overwriteCollisionCheck)
{
	Point pos = getPosition();
	pos += m_velocity * dt;
	setPosition(pos);
	updateCollider();
	if (!overwriteCollisionCheck)
		CheckForCollisions();

	if (m_affectedByGravity)
	{
		if (!m_grounded)
		{
			m_velocity.y += m_gravity * dt;
		}
		else
		{
			if(m_velocity.y < 0.0f) m_velocity.y = 0.0f;
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