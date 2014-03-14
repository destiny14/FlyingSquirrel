#include "Moveable.h"
#include "MainLayer.h"

USING_NS_CC;
using namespace std;

Moveable::Moveable(PhysicsEngine* _pEn) : Ground(_pEn)
{
	m_grounded = false;
	m_gravity = -500.0f;

	//Create Colliders
	up = new AABBCollider();
	up->setPhysicsObject(this);
	up->setTag(0);
	bot = new AABBCollider();
	bot->setPhysicsObject(this);
	bot->setTag(1);
	left = new AABBCollider();
	left->setPhysicsObject(this);
	left->setTag(2);
	right = new AABBCollider();
	right->setPhysicsObject(this);
	right->setTag(3);
	collider = new CompoundCollider();
	collider->setPhysicsObject(this);

	//Build compound Collider
	collider->addCollider(up);
	collider->addCollider(bot);
	collider->addCollider(left);
	collider->addCollider(right);
}

Moveable::~Moveable()
{
}

void Moveable::setGrounded(bool grounded)
{
	m_grounded = grounded;
}

void Moveable::update(float dt)
{
	if (!isGrounded())
	{
		velocity.y += m_gravity * dt;
	}
	else if (velocity.y < 0.0f)
	{
		velocity.y = 0.0f;
	}
	//log("vel: %f", velocity.y);
	//log("grounded: %i", isGrounded());
	m_grounded = false;
	Ground::update(dt);
}

bool Moveable::onCollision(PhysicsObject* _other, int myColliderTag)
{
	//log("myColliderTag: %i", myColliderTag);
	//log("botTag: %i", myColliderTag);
	if (myColliderTag == bot->getTag())
	{
		m_grounded = true;
		return true;
	}

	return false;
}

void Moveable::setSize(float _w, float _h)
{
	up->setBoundingRect(Rect(- _w * 0.5, _h * 0.5, _w, 5));
	bot->setBoundingRect(Rect(- _w * 0.5,- _h * 0.5, _w, 5));
	left->setBoundingRect(Rect(- _w * 0.5,- _h * 0.5 + 7.5, _w * 0.5, _h - 10));
	right->setBoundingRect(Rect(0.0f,- _h * 0.5 + 7.5, _w * 0.5, _h - 10));
	//up->setBoundingRect(Rect(0, _h * 0.5, _w, 5));
	//bot->setBoundingRect(Rect(0, 0, _w, 5));
	//left->setBoundingRect(Rect(0, 10, _w * 0.5, _h));
	//right->setBoundingRect(Rect(_w * 0.5, 10, _w * 0.5, _h));
}

void Moveable::setSizeToTexture()
{
	setSize(getTexture()->getBoundingBox().size.width, getTexture()->getBoundingBox().size.height);
}