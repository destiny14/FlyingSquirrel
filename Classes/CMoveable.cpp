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
	up->setTag(0);
	bot = new AABBCollider();
	bot->setTag(1);
	left = new AABBCollider();
	left->setTag(2);
	right = new AABBCollider();
	right->setTag(3);
	collider = new CompoundCollider();

	//Build compound Collider
	collider->addCollider(up);
	collider->addCollider(bot);
	collider->addCollider(left);
	collider->addCollider(right);
	collider->setPhysicsObject(this);
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
	else if (velocity.y <= 0.0f)
	{
		velocity.y = -1.0f;
	}

	m_grounded = false;
	Ground::update(dt);
}

bool Moveable::onCollision(PhysicsObject* _other, int myColliderTag)
{
	if (_other->getTag() != TAG_GROUND) return false;

	if (myColliderTag == bot->getTag())
	{
		m_grounded = true;
		return true;
	}

	return false;
}

void Moveable::setSize(float _w, float _h)
{
	size = Size(_w, _h);
	up->setBoundingRect(Rect(		0,			_h * 0.8f,	_w,			_h * 0.2f - 20	));
	bot->setBoundingRect(Rect(		0,			10,			_w,			_h * 0.2f - 20	));
	left->setBoundingRect(Rect(		0,			10,			_w * 0.5f,	_h -20			));
	right->setBoundingRect(Rect(	_w * 0.5f,	10,			_w * 0.5f,	_h - 20			));
}

void Moveable::setSizeToTexture()
{
	if (getTexture() == nullptr) return;

	setSize(getTexture()->getBoundingBox().size.width, getTexture()->getBoundingBox().size.height);
}