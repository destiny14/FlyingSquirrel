#include "Moveable.h"
#include "MainLayer.h"

USING_NS_CC;
using namespace std;

Moveable::Moveable(PhysicsEngine* _pEn) : Ground(_pEn)
{
	m_grounded = false;
	m_gravity = -19.62f;

	//Create Colliders
	up = new AABBCollider();
	up->setPhysicsObject(this);
	bot = new AABBCollider();
	bot->setPhysicsObject(this);
	left = new AABBCollider();
	left->setPhysicsObject(this);
	right = new AABBCollider();
	right->setPhysicsObject(this);
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

void Moveable::update(float dt)
{
	if (!isGrounded())
	{
		velocity.y += m_gravity * dt;
	}

	Ground::update(dt);
}

bool Moveable::onCollision(PhysicsObject* _other, int myColliderTag)
{
	if (myColliderTag == bot->getTag())
	{
		m_grounded = true;
		return true;
	}
}

void Moveable::setSize(float _w, float _h)
{
	//up->setBoundingRect();
}

void Moveable::setSizeToTexture()
{
	setSize(getTexture()->getBoundingBox().size.width, getTexture()->getBoundingBox().size.height);
}